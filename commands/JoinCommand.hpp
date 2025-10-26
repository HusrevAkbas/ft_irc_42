#pragma once

#include "Command.hpp"
#include <string>
#include <vector>

class JoinCommand : public Command {
private:
    std::vector<std::string> channels;
    std::vector<std::string> keys;

public:
    JoinCommand();
    JoinCommand(const std::vector<std::string>& chans, const std::vector<std::string>& keys);
    JoinCommand(const JoinCommand& other);
    JoinCommand& operator=(const JoinCommand& other);
    ~JoinCommand();

    std::vector<std::string> getChannels() const;
    std::vector<std::string> getKeys() const;
    void response(Client &client, Server &server);

private:
    std::string joinSingleChannel(Server &server, Client &client,
                                   const std::string& channelName,
                                   const std::string& key);
};
