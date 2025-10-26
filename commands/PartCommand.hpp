#pragma once

#include "Command.hpp"
#include <string>
#include <vector>

class PartCommand : public Command {
private:
    std::vector<std::string> channels;
    std::string reason;

public:
    PartCommand();
    PartCommand(const std::vector<std::string>& chans, const std::string& r);
    PartCommand(const PartCommand& other);
    PartCommand& operator=(const PartCommand& other);
    virtual ~PartCommand();

    std::vector<std::string> getChannels() const;
    std::string getReason() const;
    void response(Client &client, Server &server);

private:
    std::string partSingleChannel(Server &server, Client &client,
                                   const std::string& channelName);
};
