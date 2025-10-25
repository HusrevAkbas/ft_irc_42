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
    // TODO: implement
    (void)server;
    (void)client;
}
