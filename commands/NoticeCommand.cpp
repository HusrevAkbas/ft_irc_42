#include "NoticeCommand.hpp"

NoticeCommand::NoticeCommand() : Command("NOTICE") {}

NoticeCommand::NoticeCommand(const std::string& target, const std::string& message)
    : Command("NOTICE"), target(target), message(message) {}

NoticeCommand::NoticeCommand(const NoticeCommand& other) : Command("NOTICE") {
    *this = other;
}

NoticeCommand& NoticeCommand::operator=(const NoticeCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        target = other.target;
        message = other.message;
    }
    return *this;
}

NoticeCommand::~NoticeCommand() {}

std::string NoticeCommand::getMessage() const {
    return message;
}

std::string NoticeCommand::getTarget() const {
    return target;
}

void NoticeCommand::response(Client &client, Server &server)
{
    std::string response;

    // if target is channel
    if (this->getTarget()[0] == '#')
    {
        Channel *chan = server.findChannelByName(this->target);
        if (!chan)
            return ;
        else
        {
            response.append(":").append(client.getNickname()).append(" NOTICE ")
                .append(this->target).append(" :").append(this->message).append("\r\n");
            chan->broadcast(client, server, response);
        }
    }
    // if target is user
    else
    {
        Client *target = server.findClientByNick(this->target);
        if (!target)
            return ;
        else
        {
            response = ":" + client.getNickname() + " NOTICE " + this->target + " :" + this->message + "\r\n";
            server.sendResponse(*target, response);
        }
    }
}
