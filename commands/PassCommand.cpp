#include "PassCommand.hpp"

PassCommand::PassCommand(const std::string& pass)
    : Command("PASS"), password(pass) {}

PassCommand::~PassCommand() {}

std::string PassCommand::getPassword() const {
    return password;
}

void    PassCommand::response(Client &client, Server &server)
{
    std::string response;

    if (this->password != server.getPass())
    {
        response.append(":")
            .append(server.getName())
            .append(" 464 :Password incorrect\r\n");
        send(client.getSocketFd(), response.c_str(), response.length(), 0);
        server.removeClient(server.findClientByFd(client.getSocketFd()));
    }
}
