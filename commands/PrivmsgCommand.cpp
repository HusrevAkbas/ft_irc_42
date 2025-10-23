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
    // TODO: implement
    (void)server;
    (void)client;
}
