#ifndef PRIVMSGCOMMAND_HPP
#define PRIVMSGCOMMAND_HPP

#include "Command.hpp"
#include <string>

class PrivmsgCommand : public Command {
private:
    std::string target;
    std::string message;

public:
    PrivmsgCommand(const std::string& tgt, const std::string& msg);
    virtual ~PrivmsgCommand();

    std::string getTarget() const;
    std::string getMessage() const;
};

#endif
