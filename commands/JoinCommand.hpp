#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include "Command.hpp"
#include <string>

class JoinCommand : public Command {
private:
    std::string channel;
    std::string key;

public:
    JoinCommand(const std::string& chan, const std::string& k = "");
    virtual ~JoinCommand();

    std::string getChannel() const;
    std::string getKey() const;
};

#endif
