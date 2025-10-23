#pragma once

#include "Command.hpp"
#include <string>

class CapCommand : public Command {
private:
    std::string subcommand;
    std::string capabilities;

public:
    CapCommand();
    CapCommand(const std::string& subcmd, const std::string& caps);
    CapCommand(const CapCommand& other);
    CapCommand& operator=(const CapCommand& other);
    ~CapCommand();

    std::string getSubcommand() const;
    std::string getCapabilities() const;
    void response(Client &client, Server &server);
};
