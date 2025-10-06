#include "Command.hpp"

Command::Command(const std::string& cmdType) : type(cmdType) {}

Command::~Command() {}

std::string Command::getType() const {
    return type;
}
