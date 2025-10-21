#include "QuitCommand.hpp"

QuitCommand::QuitCommand(const std::string& msg)
    : Command("QUIT"), message(msg) {}

QuitCommand::~QuitCommand() {}

std::string QuitCommand::getMessage() const {
    return message;
}
