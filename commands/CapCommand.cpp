#include "CapCommand.hpp"

CapCommand::CapCommand() : Command("CAP") {}

CapCommand::CapCommand(const std::string& subcmd, const std::string& caps)
    : Command("CAP"), subcommand(subcmd), capabilities(caps) {}

CapCommand::CapCommand(const CapCommand& other) : Command("CAP") {
    *this = other;
}

CapCommand& CapCommand::operator=(const CapCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        subcommand = other.subcommand;
        capabilities = other.capabilities;
    }
    return *this;
}

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
        server.sendResponse(client, response);
    if (this->subcommand == "END")
        client.setConnected(1);
}
