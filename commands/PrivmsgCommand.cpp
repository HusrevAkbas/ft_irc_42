#include "PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand(const std::string& tgt, const std::string& msg)
    : Command("PRIVMSG"), target(tgt), message(msg) {}

PrivmsgCommand::~PrivmsgCommand() {}

std::string PrivmsgCommand::getTarget() const {
    return target;
}

std::string PrivmsgCommand::getMessage() const {
    return message;
}
