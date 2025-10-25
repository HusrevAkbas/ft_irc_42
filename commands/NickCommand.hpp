#pragma once

#include "Command.hpp"
#include <string>

class NickCommand : public Command {
private:
    std::string nickname;

public:
    NickCommand();
    NickCommand(const std::string& nick);
    NickCommand(const NickCommand& other);
    NickCommand& operator=(const NickCommand& other);
    ~NickCommand();

    std::string getNickname() const;
    void response(Client &client, Server &server);
};
