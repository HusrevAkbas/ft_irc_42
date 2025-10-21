#include "JoinCommand.hpp"

JoinCommand::JoinCommand(const std::string& chan, const std::string& k)
    : Command("JOIN"), channel(chan), key(k) {}

JoinCommand::~JoinCommand() {}

std::string JoinCommand::getChannel() const {
    return channel;
}

std::string JoinCommand::getKey() const {
    return key;
}
