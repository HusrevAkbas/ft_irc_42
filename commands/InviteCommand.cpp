#include "InviteCommand.hpp"

InviteCommand::InviteCommand() : Command("INVITE") {}

InviteCommand::InviteCommand(const std::string& nick, const std::string& chan)
    : Command("INVITE"), nickname(nick), channel(chan) {}

InviteCommand::InviteCommand(const InviteCommand& other) : Command("INVITE") {
    *this = other;
}

InviteCommand& InviteCommand::operator=(const InviteCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        nickname = other.nickname;
        channel = other.channel;
    }
    return *this;
}

InviteCommand::~InviteCommand() {}

std::string InviteCommand::getNickname() const {
    return nickname;
}

std::string InviteCommand::getChannel() const {
    return channel;
}

void InviteCommand::response(Client &client, Server &server)
{
    // TODO: implement
    (void)server;
    (void)client;
}
