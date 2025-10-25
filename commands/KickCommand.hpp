#pragma once

#include "Command.hpp"
#include <string>

class KickCommand : public Command {
private:
    std::string channel;
    std::string user;
    std::string reason;

public:
    KickCommand();
    KickCommand(const std::string& chan, const std::string& usr, const std::string& rsn);
    KickCommand(const KickCommand& other);
    KickCommand& operator=(const KickCommand& other);
    virtual ~KickCommand();

    std::string getChannel() const;
    std::string getUser() const;
    std::string getReason() const;
    void response(Client &client, Server &server);
};
