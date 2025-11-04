#include "JoinCommand.hpp"
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../Client.hpp"
#include <sstream>

JoinCommand::JoinCommand() : Command("JOIN") {}

JoinCommand::JoinCommand(const std::vector<std::string>& chans, const std::vector<std::string>& keys)
    : Command("JOIN"), channels(chans), keys(keys) {}

JoinCommand::JoinCommand(const JoinCommand& other) : Command("JOIN") {
    *this = other;
}

JoinCommand& JoinCommand::operator=(const JoinCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        channels = other.channels;
        keys = other.keys;
    }
    return *this;
}

JoinCommand::~JoinCommand() {}

std::vector<std::string> JoinCommand::getChannels() const {
    return channels;
}

std::vector<std::string> JoinCommand::getKeys() const {
    return keys;
}

void JoinCommand::response(Client &client, Server &server)
{
    std::string response;

    if (channels.size() == 1 && channels[0] == "0")
    {
        std::vector<Channel *> clientChannels = client.getChannels();
        for (size_t i = 0; i < clientChannels.size(); i++)
        {
            Channel *chan = clientChannels[i];
            std::string channelName = chan->getName();

            chan->removeClient(client);
            client.removeChannel(chan);

            response += buildClientMessage(client, "PART", channelName);
        }
        server.sendResponse(client, response);
        return;
    }

    for (size_t i = 0; i < channels.size(); i++)
    {
        std::string channelName = channels[i];
        std::string key = (i < keys.size()) ? keys[i] : "";

        response += joinSingleChannel(server, client, channelName, key);
    }

    server.sendResponse(client, response);
}

std::string JoinCommand::joinSingleChannel(Server &server, Client &client,
                                           const std::string& channelName,
                                           const std::string& key)
{
    std::string response;
    Channel *chan = server.findChannelByName(channelName);

    if (!chan)
    {
        if (server.getChannels().size() >= MAX_CHANNELS)
        {
            response = buildNumericReply(server, client, ERR_TOOMANYCHANNELS, channelName, "You have joined too many channels");
            return response;
        }

        chan = new Channel(channelName);
        server.addChannel(chan);

        chan->addClient(client);
        chan->addOperator(client);
        client.addChannel(chan);
    }
    else
    {
        if (chan->isClientInChannel(client))
        {
            return "";
        }

        if (chan->getPassStatus())
        {
            if (key.empty() || key != chan->getPass())
            {
                response = buildNumericReply(server, client, ERR_BADCHANNELKEY, channelName, "Cannot join channel (+k)");
                return response;
            }
        }

        if (chan->getInviteStatus())
        {
            response = buildNumericReply(server, client, ERR_INVITEONLYCHAN, channelName, "Cannot join channel (+i)");
            return response;
        }

        if (chan->getUserLimit() > 0 &&
            (int)chan->getClients().size() >= chan->getUserLimit())
        {
            response = buildNumericReply(server, client, ERR_CHANNELISFULL, channelName, "Cannot join channel (+l)");
            return response;
        }

        chan->addClient(client);
        client.addChannel(chan);
    }

    response = buildClientMessage(client, "JOIN", channelName);

    if (!chan->getTopic().empty())
    {
        response += buildNumericReply(server, client, RPL_TOPIC, channelName, chan->getTopic());
    }

    std::string namesList;
    std::vector<Client *> clients = chan->getClients();
    std::vector<Client *> operators = chan->getOperators();
    for (size_t i = 0; i < clients.size(); i++)
    {
        bool isOp = false;
        for (size_t j = 0; j < operators.size(); j++)
        {
            if (clients[i] == operators[j])
            {
                isOp = true;
                break;
            }
        }
        if (isOp)
            namesList += "@";
        namesList += clients[i]->getNickname();
        if (i < clients.size() - 1)
            namesList += " ";
    }

    response += buildNameReply(server, client, channelName, namesList);
    response += buildNumericReply(server, client, RPL_ENDOFNAMES, channelName, "End of /NAMES list");

    return response;
}
