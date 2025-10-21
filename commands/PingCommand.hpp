#ifndef PINGCOMMAND_HPP
#define PINGCOMMAND_HPP

#include "Command.hpp"
#include <string>

class PingCommand : public Command {
private:
    std::string server;

public:
    PingCommand(const std::string& srv);
    virtual ~PingCommand();

    std::string getServer() const;
};

#endif
