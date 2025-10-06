#include "ModeCommand.hpp"

ModeCommand::ModeCommand(const std::string& chan, const std::string& mod, const std::string& params)
    : Command("MODE"), channel(chan), mode(mod), modeParams(params) {}

ModeCommand::~ModeCommand() {}

std::string ModeCommand::getChannel() const {
    return channel;
}

std::string ModeCommand::getMode() const {
    return mode;
}

std::string ModeCommand::getModeParams() const {
    return modeParams;
}
