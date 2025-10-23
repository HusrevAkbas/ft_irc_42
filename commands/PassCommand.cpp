#include "PassCommand.hpp"

PassCommand::PassCommand() : Command("PASS") {}

PassCommand::PassCommand(const std::string& pass)
    : Command("PASS"), password(pass) {}

PassCommand::PassCommand(const PassCommand& other) : Command("PASS") {
    *this = other;
}

PassCommand& PassCommand::operator=(const PassCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        password = other.password;
    }
    return *this;
}

PassCommand::~PassCommand() {}

std::string PassCommand::getPassword() const {
    return password;
}

void PassCommand::response(Client &client, Server &server)
{
    // TODO: implement
    (void)server;
    (void)client;
}
