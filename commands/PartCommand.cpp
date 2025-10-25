#include "PartCommand.hpp"

PartCommand::PartCommand() : Command("PART") {}

PartCommand::PartCommand(const std::vector<std::string>& chans, const std::string& r)
    : Command("PART"), channels(chans), reason(r) {}

PartCommand::PartCommand(const PartCommand& other) : Command("PART") {
    *this = other;
}

PartCommand& PartCommand::operator=(const PartCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        channels = other.channels;
        reason = other.reason;
    }
    return *this;
}

PartCommand::~PartCommand() {}

std::vector<std::string> PartCommand::getChannels() const {
    return channels;
}

std::string PartCommand::getReason() const {
    return reason;
}

void PartCommand::response(Client &client, Server &server)
{
    std::string response;

    if (channels.empty())
    {
        response = buildNumericReply(server, client, ERR_NEEDMOREPARAMS, "PART :Not enough parameters");
        server.sendResponse(client, response);
        return;
    }

    for (size_t i = 0; i < channels.size(); i++)
    {
        response += partSingleChannel(server, client, channels[i]);
    }

    server.sendResponse(client, response);
}

std::string PartCommand::partSingleChannel(Server &server, Client &client,
                                           const std::string& channelName)
{
    std::string response;

    if (channelName.empty())
    {
        return response;
    }

    Channel *chan = server.findChannelByName(channelName);

    if (!chan)
    {
        return buildNumericReply(server, client, ERR_NOSUCHCHANNEL, channelName, "No such channel");
    }

    if (!chan->isClientInChannel(client))
    {
        return buildNumericReply(server, client, ERR_NOTONCHANNEL, channelName, "You're not on that channel");
    }

    std::string params = channelName;
    if (!reason.empty())
    {
        params += " :";
        params += reason;
    }
    std::string partMessage = buildClientMessage(client, "PART", params);

    chan->removeClient(client);

    if (chan->isOperator(client))
    {
        chan->removeOperator(client);
    }

    client.removeChannel(chan);

    if (chan->getClients().empty())
    {
        server.removeChannel(chan);
        delete chan;
    }

    response = partMessage;

    return response;
}
