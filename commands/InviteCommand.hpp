#pragma once

#include "Command.hpp"
#include <string>

class InviteCommand : public Command {
private:
    std::string nickname;
    std::string channel;

public:
    InviteCommand();
    InviteCommand(const std::string& nick, const std::string& chan);
    InviteCommand(const InviteCommand& other);
    InviteCommand& operator=(const InviteCommand& other);
    virtual ~InviteCommand();

    std::string getNickname() const;
    std::string getChannel() const;
    void response(Client &client, Server &server);
};
