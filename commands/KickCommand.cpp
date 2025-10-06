#include "KickCommand.hpp"

KickCommand::KickCommand(const std::string& chan, const std::string& usr, const std::string& rsn)
    : Command("KICK"), channel(chan), user(usr), reason(rsn) {}

KickCommand::~KickCommand() {}

std::string KickCommand::getChannel() const {
    return channel;
}

std::string KickCommand::getUser() const {
    return user;
}

std::string KickCommand::getReason() const {
    return reason;
}