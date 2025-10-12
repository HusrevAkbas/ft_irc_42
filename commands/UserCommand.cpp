#include "UserCommand.hpp"

UserCommand::UserCommand(const std::string& user, const std::string& real)
    : Command("USER"), username(user), realname(real) {}

UserCommand::~UserCommand() {}

std::string UserCommand::getUsername() const {
    return username;
}

std::string UserCommand::getRealname() const {
    return realname;
}
