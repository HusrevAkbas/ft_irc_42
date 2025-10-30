#include "UserCommand.hpp"

UserCommand::UserCommand() : Command("USER") {}

UserCommand::UserCommand(const std::string& user, const std::string& real)
    : Command("USER"), username(user), realname(real) {}

UserCommand::UserCommand(const UserCommand& other) : Command("USER") {
    *this = other;
}

UserCommand& UserCommand::operator=(const UserCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        username = other.username;
        realname = other.realname;
    }
    return *this;
}

UserCommand::~UserCommand() {}

std::string UserCommand::getUsername() const {
    return username;
}

std::string UserCommand::getRealname() const {
    return realname;
}

void UserCommand::response(Client &client, Server &server)
{
    std::string response;

    if (client.getConnected())
    {
        response = Command::buildNumericReply(server, client, ERR_ALREADYREGISTERED, "You are already registered");
        server.sendResponse(client, response);
        return ;
    }
    // TODO set also hostname and network name
    client.setUsername(this->username);
    client.setRealname(this->realname);
}
