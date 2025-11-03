#include "NickCommand.hpp"

NickCommand::NickCommand() : Command("NICK") {}

NickCommand::NickCommand(const std::string& nick)
    : Command("NICK"), nickname(nick) {}

NickCommand::NickCommand(const NickCommand& other) : Command("NICK") {
    *this = other;
}

NickCommand& NickCommand::operator=(const NickCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        nickname = other.nickname;
    }
    return *this;
}

NickCommand::~NickCommand() {}

std::string NickCommand::getNickname() const {
    return nickname;
}

void NickCommand::response(Client &client, Server &server)
{
    std::string response;
    std::string msg;

    // check if nickname exist
    if (this->nickname.empty())
    {
        if (!client.getConnected())
        {
            server.removeClient(&client);
            return ; // throw std::invalid_argument("No nickname given");
        }
        msg = "No nickname given";
        response = Command::buildNumericReply(server, client, ERR_NONICKNAMEGIVEN, msg);
        server.sendResponse(client, response);
    }
    // set client nickname
    else
    {
        if (!client.getNickname().empty())
        {
            response =":" + client.getNickname() + " NICK " + this->nickname + "\r\n";
            server.sendResponse(client, response);
        }
        client.setNickname(this->nickname);
    }
}
