#pragma once

#include "Command.hpp"
#include <string>

class TopicCommand : public Command {
private:
    std::string channel;
    std::string topic;

public:
    TopicCommand();
    TopicCommand(const std::string& chan, const std::string& top);
    TopicCommand(const TopicCommand& other);
    TopicCommand& operator=(const TopicCommand& other);
    ~TopicCommand();

    std::string getChannel() const;
    std::string getTopic() const;
    void response(Client &client, Server &server);
};
