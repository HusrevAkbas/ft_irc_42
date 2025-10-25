#pragma once

#include "Command.hpp"
#include <string>

class PrivmsgCommand : public Command {
private:
    std::string target;
    std::string message;

public:
    PrivmsgCommand();
    PrivmsgCommand(const std::string& tgt, const std::string& msg);
    PrivmsgCommand(const PrivmsgCommand& other);
    PrivmsgCommand& operator=(const PrivmsgCommand& other);
    ~PrivmsgCommand();

    std::string getTarget() const;
    std::string getMessage() const;
    void response(Client &client, Server &server);
};
