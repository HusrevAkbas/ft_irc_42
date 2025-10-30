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
            server.removeClient(server.findClientByFd(client.getSocketFd()));
            throw std::invalid_argument("No nickname given");
        }
        msg = "No nickname given";
        response = Command::buildNumericReply(server, client, ERR_NONICKNAMEGIVEN, msg);
    }
    // if nickname is already in use send deny message, if not registered close connection
    else if (server.findClientByNick(this->getNickname()))
    {
        msg = "Nickname is already in use";
        response = Command::buildNumericReply(server, client, ERR_NICKNAMEINUSE, "Nickname is already in use");
        send(client.getSocketFd(), response.c_str(), response.length(), 0);
        if (!client.getConnected())
        {
            server.removeClient(server.findClientByFd(client.getSocketFd()));
            throw std::invalid_argument("Nickname is in use");
        }
    }
    // set client nickname
    else
    {
        if (!client.getNickname().empty())
        {
            response.append(":").append(client.getNickname()). append(" NICK ").append(this->nickname).append("\r\n");
            server.sendResponse(client, response);
        }
        client.setNickname(this->nickname);
    }
}
