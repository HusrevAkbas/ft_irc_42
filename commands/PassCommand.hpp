#pragma once

#include "Command.hpp"
#include <string>

class PassCommand : public Command {
private:
    std::string password;

public:
    PassCommand();
    PassCommand(const std::string& pass);
    PassCommand(const PassCommand& other);
    PassCommand& operator=(const PassCommand& other);
    ~PassCommand();

    std::string getPassword() const;
    void response(Client &client, Server &server);
};
