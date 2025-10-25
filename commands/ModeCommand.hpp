#pragma once

#include "Command.hpp"
#include <string>

class ModeCommand : public Command {
private:
    std::string target;
    std::string modeString;
    std::string modeParams;

public:
    ModeCommand();
    ModeCommand(const std::string& tgt, const std::string& modeStr, const std::string& params);
    ModeCommand(const ModeCommand& other);
    ModeCommand& operator=(const ModeCommand& other);
    ~ModeCommand();

    std::string getTarget() const;
    std::string getModeString() const;
    std::string getModeParams() const;
    void response(Client &client, Server &server);
};
