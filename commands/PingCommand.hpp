#pragma once

#include "Command.hpp"
#include <string>

class PingCommand : public Command {
private:
    std::string server;

public:
    PingCommand();
    PingCommand(const std::string& srv);
    PingCommand(const PingCommand& other);
    PingCommand& operator=(const PingCommand& other);
    ~PingCommand();

    std::string getServer() const;
    void response(Client &client, Server &server);
};
