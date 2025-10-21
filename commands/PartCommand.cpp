#include "PartCommand.hpp"

PartCommand::PartCommand(const std::string& chan, const std::string& r)
    : Command("PART"), channel(chan), reason(r) {}

PartCommand::~PartCommand() {}

std::string PartCommand::getChannel() const {
    return channel;
}

std::string PartCommand::getReason() const {
    return reason;
}
