#include "NickCommand.hpp"

NickCommand::NickCommand(const std::string& nick)
    : Command("NICK"), nickname(nick) {}

NickCommand::~NickCommand() {}

std::string NickCommand::getNickname() const {
    return nickname;
}
