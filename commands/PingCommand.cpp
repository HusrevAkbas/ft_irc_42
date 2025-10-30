#include "PingCommand.hpp"

PingCommand::PingCommand() : Command("PING") {}

PingCommand::PingCommand(const std::string& srv)
    : Command("PING"), server(srv) {}

PingCommand::PingCommand(const PingCommand& other) : Command("PING") {
    *this = other;
}

PingCommand& PingCommand::operator=(const PingCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        server = other.server;
    }
    return *this;
}

PingCommand::~PingCommand() {}

std::string PingCommand::getServer() const {
    return server;
}

void PingCommand::response(Client &client, Server &server)
{
    (void)server;
    std::string response = "PONG ";

    response += this->getServer();
    response += "\r\n";
    server.sendResponse(client, response);
}
