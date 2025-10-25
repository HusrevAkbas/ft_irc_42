#pragma once

#include "Command.hpp"
#include <string>

class UserCommand : public Command {
private:
    std::string username;
    std::string realname;

public:
    UserCommand();
    UserCommand(const std::string& user, const std::string& real);
    UserCommand(const UserCommand& other);
    UserCommand& operator=(const UserCommand& other);
    ~UserCommand();

    std::string getUsername() const;
    std::string getRealname() const;
    void response(Client &client, Server &server);
};
