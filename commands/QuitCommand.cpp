#include "QuitCommand.hpp"

QuitCommand::QuitCommand() : Command("QUIT") {}

QuitCommand::QuitCommand(const std::string& msg)
    : Command("QUIT"), message(msg) {}

QuitCommand::QuitCommand(const QuitCommand& other) : Command("QUIT") {
    *this = other;
}

QuitCommand& QuitCommand::operator=(const QuitCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        message = other.message;
    }
    return *this;
}

QuitCommand::~QuitCommand() {}

std::string QuitCommand::getMessage() const {
    return message;
}

void QuitCommand::response(Client &client, Server &server)
{
    // TODO: implement
    (void)server;
    (void)client;
}
