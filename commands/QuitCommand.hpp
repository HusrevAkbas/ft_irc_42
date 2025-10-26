#pragma once

#include "Command.hpp"
#include <string>

class QuitCommand : public Command {
private:
    std::string message;

public:
    QuitCommand();
    QuitCommand(const std::string& msg);
    QuitCommand(const QuitCommand& other);
    QuitCommand& operator=(const QuitCommand& other);
    ~QuitCommand();

    std::string getMessage() const;
    void response(Client &client, Server &server);
};
