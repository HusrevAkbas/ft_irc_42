#include "InviteCommand.hpp"

InviteCommand::InviteCommand(const std::string& nick, const std::string& chan)
    : Command("INVITE"), nickname(nick), channel(chan) {}

InviteCommand::~InviteCommand() {}

std::string InviteCommand::getNickname() const {
    return nickname;
}

std::string InviteCommand::getChannel() const {
    return channel;
}
