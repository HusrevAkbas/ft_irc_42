#include "ModeCommand.hpp"
#include "../Channel.hpp"
#include "../Server.hpp"
#include "../Client.hpp"
#include <sstream>
#include <vector>

ModeCommand::ModeCommand() : Command("MODE") {}

ModeCommand::ModeCommand(const std::string& tgt, const std::string& modeStr, const std::string& params)
    : Command("MODE"), target(tgt), modeString(modeStr), modeParams(params) {}

ModeCommand::ModeCommand(const ModeCommand& other) : Command("MODE") {
    *this = other;
}

ModeCommand& ModeCommand::operator=(const ModeCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        target = other.target;
        modeString = other.modeString;
        modeParams = other.modeParams;
    }
    return *this;
}

ModeCommand::~ModeCommand() {}

std::string ModeCommand::getTarget() const {
    return target;
}

std::string ModeCommand::getModeString() const {
    return modeString;
}

std::string ModeCommand::getModeParams() const {
    return modeParams;
}

static std::vector<std::string> splitParams(const std::string& params)
{
    std::vector<std::string> result;
    std::stringstream ss(params);
    std::string token;

    while (ss >> token)
    {
        result.push_back(token);
    }
    return result;
}

static std::string getCurrentModes(Channel *chan)
{
    std::string modes = "+";
    std::string modeParams = "";

    if (chan->getInviteStatus())
        modes += "i";
    if (chan->getTopicStatus())
        modes += "t";
    if (chan->getPassStatus())
    {
        modes += "k";
        modeParams += " " + chan->getPass();
    }
    if (chan->getUserLimit() > 0)
    {
        modes += "l";
        std::stringstream ss;
        ss << chan->getUserLimit();
        modeParams += " " + ss.str();
    }

    return modes + modeParams;
}

void ModeCommand::response(Client &client, Server &server)
{
    std::string response;
    std::string targetName = this->target;
    std::string modes = this->modeString;
    std::string params = this->modeParams;

    if (targetName.empty())
    {
        response = buildNumericReply(server, client, ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");
        server.sendResponse(client, response);
        return;
    }

    Channel *chan = server.findChannelByName(targetName);

    if (!chan)
    {
        response = buildNumericReply(server, client, ERR_NOSUCHCHANNEL, targetName, "No such channel");
        server.sendResponse(client, response);
        return;
    }

    if (!chan->isClientInChannel(client))
    {
        response = buildNumericReply(server, client, ERR_NOTONCHANNEL, targetName, "You're not on that channel");
        server.sendResponse(client, response);
        return;
    }

    if (modes.empty())
    {
        response = buildNumericReplyNoColon(server, client, RPL_CHANNELMODEIS, targetName, getCurrentModes(chan));
        server.sendResponse(client, response);
        return;
    }

    if (!chan->isOperator(client))
    {
        response = buildNumericReply(server, client, ERR_CHANOPRIVSNEEDED, targetName, "You're not channel operator");
        server.sendResponse(client, response);
        return;
    }

    bool adding = true;
    std::vector<std::string> paramsList = splitParams(params);
    size_t paramIndex = 0;
    std::string appliedModes = "";
    std::string appliedParams = "";

    for (size_t i = 0; i < modes.length(); i++)
    {
        char modeChar = modes[i];

        if (modeChar == '+')
        {
            adding = true;
            if (appliedModes.empty() || appliedModes[appliedModes.length() - 1] != '+')
                appliedModes += "+";
        }
        else if (modeChar == '-')
        {
            adding = false;
            if (appliedModes.empty() || appliedModes[appliedModes.length() - 1] != '-')
                appliedModes += "-";
        }
        else if (modeChar == 'i')
        {
            chan->setInviteOnly(adding);
            appliedModes += "i";
        }
        else if (modeChar == 't')
        {
            chan->setTopicSetable(adding);
            appliedModes += "t";
        }
        else if (modeChar == 'k')
        {
            if (adding)
            {
                if (paramIndex < paramsList.size())
                {
                    std::string key = paramsList[paramIndex++];
                    chan->setPassword(key);
                    chan->setUsePassword(true);
                    appliedModes += "k";
                    appliedParams += " " + key;
                }
            }
            else
            {
                chan->setPassword("");
                chan->setUsePassword(false);
                appliedModes += "k";
            }
        }
        else if (modeChar == 'o')
        {
            if (paramIndex < paramsList.size())
            {
                std::string targetNick = paramsList[paramIndex++];
                Client *targetClient = server.findClientByNick(targetNick);

                if (targetClient && chan->isClientInChannel(*targetClient))
                {
                    if (adding)
                        chan->addOperator(*targetClient);
                    else
                        chan->removeOperator(*targetClient);
                    appliedModes += "o";
                    appliedParams += " " + targetNick;
                }
            }
        }
        else if (modeChar == 'l')
        {
            if (adding)
            {
                if (paramIndex < paramsList.size())
                {
                    std::string limitStr = paramsList[paramIndex++];
                    std::stringstream ss(limitStr);
                    int limit;
                    if (ss >> limit && limit > 0)
                    {
                        chan->setUserLimit(limit);
                        appliedModes += "l";
                        appliedParams += " " + limitStr;
                    }
                }
            }
            else
            {
                chan->setUserLimit(0);
                appliedModes += "l";
            }
        }
        else
        {
            std::string modeCharStr(1, modeChar);
            response = buildNumericReply(server, client, ERR_UNKNOWNMODE, modeCharStr, "is unknown mode char to me");
            server.sendResponse(client, response);
            return;
        }
    }

    if (!appliedModes.empty())
    {
        std::string params = targetName + " " + appliedModes + appliedParams;
        response = buildClientMessage(client, "MODE", params);
        server.sendResponse(client, response);
        return;
    }

    response = "";
    server.sendResponse(client, response);
}
