#ifndef PARTCOMMAND_HPP
#define PARTCOMMAND_HPP

#include "Command.hpp"
#include <string>

class PartCommand : public Command {
private:
    std::string channel;
    std::string reason;

public:
    PartCommand(const std::string& chan, const std::string& r = "");
    virtual ~PartCommand();

    std::string getChannel() const;
    std::string getReason() const;
};

#endif
