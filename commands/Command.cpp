#include "Command.hpp"
#include "../Server.hpp"
#include "../Client.hpp"

Command::Command() : type("") {}

Command::Command(const std::string& cmdType) : type(cmdType) {}

Command::Command(const Command& other) : type("") {
    *this = other;
}

Command& Command::operator=(const Command& other) {
    if (this != &other) {
        type = other.type;
    }
    return *this;
}

Command::~Command() {}

std::string Command::getType() const {
    return type;
}

std::string Command::buildNumericReply(Server &server, Client &client,
                                       IrcReply replyCode,
                                       const std::string& message)
{
    std::string response = ":";
    response += server.getName();
    response += " ";
    response += toString(replyCode);
    response += " ";
    response += client.getNickname();
    response += " :";
    response += message;
    response += "\r\n";
    return response;
}

std::string Command::buildNumericReply(Server &server, Client &client,
                                       IrcReply replyCode,
                                       const std::string& target,
                                       const std::string& message)
{
    std::string response = ":";
    response += server.getName();
    response += " ";
    response += toString(replyCode);
    response += " ";
    response += client.getNickname();
    response += " ";
    response += target;
    response += " :";
    response += message;
    response += "\r\n";
    return response;
}

std::string Command::buildClientMessage(Client &client,
                                        const std::string& command,
                                        const std::string& params)
{
    std::string response = ":";
    response += client.getNickname();
    response += "!";
    response += client.getHostname();
    response += "@";
    response += client.getNetworkname();
    response += " ";
    response += command;
    if (!params.empty())
    {
        response += " ";
        response += params;
    }
    response += "\r\n";
    return response;
}

std::string Command::buildNameReply(Server &server, Client &client,
                                    const std::string& channelName,
                                    const std::string& namesList)
{
    std::string response = ":";
    response += server.getName();
    response += " 353 ";
    response += client.getNickname();
    response += " = ";
    response += channelName;
    response += " :";
    response += namesList;
    response += "\r\n";
    return response;
}

std::string Command::buildNumericReplyNoColon(Server &server, Client &client,
                                               IrcReply replyCode,
                                               const std::string& target,
                                               const std::string& param)
{
    std::string response = ":";
    response += server.getName();
    response += " ";
    response += toString(replyCode);
    response += " ";
    response += client.getNickname();
    response += " ";
    response += target;
    response += " ";
    response += param;
    response += "\r\n";
    return response;
}
