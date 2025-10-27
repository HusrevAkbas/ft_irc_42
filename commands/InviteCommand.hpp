#pragma once

#include "Command.hpp"
#include <string>

class InviteCommand : public Command {
private:
    std::string _nickname;
    std::string _channel;

public:
    InviteCommand();
    InviteCommand(const std::string& nickname, const std::string& channel);
    InviteCommand(const InviteCommand& other);
    InviteCommand& operator=(const InviteCommand& other);
    virtual ~InviteCommand();

    std::string getNickname() const;
    std::string getChannel() const;

    bool        checkParams(Client& client);
    Client*     findUser(const std::string& nickname, Channel* channel);
    void        execute(Server& server, Client& client);
    void        response(Client &client, Server &server);
};
