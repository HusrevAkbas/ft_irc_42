#ifndef INVITECOMMAND_HPP
#define INVITECOMMAND_HPP

#include "Command.hpp"
#include <string>

class InviteCommand : public Command {
private:
    std::string nickname;
    std::string channel;

public:
    InviteCommand(const std::string& nick, const std::string& chan);
    virtual ~InviteCommand();

    std::string getNickname() const;
    std::string getChannel() const;
};

#endif
