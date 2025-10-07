#ifndef KICKCOMMAND_HPP
#define KICKCOMMAND_HPP

#include "Command.hpp"
#include <string>

class KickCommand : public Command {
private:
    std::string channel;
    std::string user;
    std::string reason;

public:
    KickCommand(const std::string& chan, const std::string& usr, const std::string& rsn);
    virtual ~KickCommand();

    std::string getChannel() const;
    std::string getUser() const;
    std::string getReason() const;
};

#endif
