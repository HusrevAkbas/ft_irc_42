#include "PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand() : Command("PRIVMSG") {}

PrivmsgCommand::PrivmsgCommand(const std::string& tgt, const std::string& msg)
    : Command("PRIVMSG"), target(tgt), message(msg) {}

PrivmsgCommand::PrivmsgCommand(const PrivmsgCommand& other) : Command("PRIVMSG") {
    *this = other;
}

PrivmsgCommand& PrivmsgCommand::operator=(const PrivmsgCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        target = other.target;
        message = other.message;
    }
    return *this;
}

PrivmsgCommand::~PrivmsgCommand() {}

std::string PrivmsgCommand::getTarget() const {
    return target;
}

std::string PrivmsgCommand::getMessage() const {
    return message;
}

void PrivmsgCommand::response(Client &client, Server &server)
{
    std::string response;

    // if there is a prefix '@' means only operators get the message

    // if target is channel
    if (this->getTarget()[0] == '#')
    {
        Channel *chan = server.findChannelByName(this->target);
        if (!chan)
        {
            //sent err msg
            response = Command::buildNumericReply(server, client, ERR_NOSUCHCHANNEL, "No such channel");
            server.sendResponse(client, response);
        }
        else
        {
            response.append(":").append(client.getNickname()).append(" PRIVMSG ")
                .append(this->target).append(" :").append(this->message).append("\n");
            chan->broadcast(client, server, response);
        }
    }
    // if target is user
    else
    {
        Client *target = server.findClientByNick(this->target);
        if (!target)
        {
            response = Command::buildNumericReplyNoColon(server, client, ERR_NOSUCHNICK, this->target,"");
            server.sendResponse(client, response);
        }
        else
        {
            response.append(":").append(client.getNickname()).append(" PRIVMSG ")
                .append(this->target).append(" :").append(this->message).append("\n");
            server.sendResponse(*target, response);
        }
    }
}
