#include "KickCommand.hpp"

KickCommand::KickCommand() : Command("KICK") {}

KickCommand::KickCommand(const std::string& chan, const std::string& usr, const std::string& rsn)
    : Command("KICK"), channel(chan), user(usr), reason(rsn) {}

KickCommand::KickCommand(const KickCommand& other) : Command("KICK") {
    *this = other;
}

KickCommand& KickCommand::operator=(const KickCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        channel = other.channel;
        user = other.user;
        reason = other.reason;
    }
    return *this;
}

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

void KickCommand::response(Client &client, Server &server)
{
    // TODO: implement
    (void)server;
    (void)client;
}