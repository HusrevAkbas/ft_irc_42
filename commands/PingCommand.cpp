#include "PingCommand.hpp"

PingCommand::PingCommand(const std::string& srv)
    : Command("PING"), server(srv) {}

PingCommand::~PingCommand() {}

std::string PingCommand::getServer() const {
    return server;
}
