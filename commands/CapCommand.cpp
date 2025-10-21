#include "CapCommand.hpp"

CapCommand::CapCommand(const std::string& subcmd, const std::string& caps)
    : Command("CAP"), subcommand(subcmd), capabilities(caps) {}

CapCommand::~CapCommand() {}

std::string CapCommand::getSubcommand() const {
    return subcommand;
}

std::string CapCommand::getCapabilities() const {
    return capabilities;
}