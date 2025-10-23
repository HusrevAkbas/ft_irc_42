#include "CapCommand.hpp"

CapCommand::CapCommand(const std::string& subcmd, const std::string& caps)
    : Command("CAP"), subcommand(subcmd), capabilities(caps) {}

CapCommand::~CapCommand() {}

std::string CapCommand::getSubcommand() const {
    return subcommand;
}

std::string CapCommand::getCapabilities() const {
    return capabilities;
}

void    CapCommand::response(Client &client, Server &server)
{
    std::string response;

    response.append(":")
        .append(server.getName())
        .append(" CAP * LS\r\n");
    if (this->subcommand == "LS")
        send(client.getSocketFd(), response.c_str(), response.length(), 0);
    if (this->subcommand == "END")
        client.setConnected(1);
}
