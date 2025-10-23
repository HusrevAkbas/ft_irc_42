#include "NickCommand.hpp"

NickCommand::NickCommand(const std::string& nick)
    : Command("NICK"), nickname(nick) {}

NickCommand::~NickCommand() {}

std::string NickCommand::getNickname() const {
    return nickname;
}

void NickCommand::response(Client &client, Server &server)
{
    std::string response;

    std::cout << server.findClientByNick(this->getNickname()) << "\n";

    if (server.findClientByNick(this->getNickname()))
    {
        response.append(":")
            .append(server.getName())
            .append(" ")
            .append(this->getNickname())
            .append(" :Nickname is already in use\r\n");
        if (client.getNickname().empty())
            server.removeClient(server.findClientByFd(client.getSocketFd()));
    }
    else
    {
        response.append(":")
            .append(client.getNickname())
            .append(" NICK ")
            .append(this->getNickname())
            .append(" :")
            .append(client.getNickname())
            .append(" changed nickname to ")
            .append(this->getNickname())
            .append("\r\n");
        client.setNickname(this->getNickname());
    }
}
