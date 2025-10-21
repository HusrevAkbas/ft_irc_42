#include "PassCommand.hpp"

PassCommand::PassCommand(const std::string& pass)
    : Command("PASS"), password(pass) {}

PassCommand::~PassCommand() {}

std::string PassCommand::getPassword() const {
    return password;
}
