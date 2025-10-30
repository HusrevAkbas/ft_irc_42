#pragma once

#include "Command.hpp"
#include <string>

class TopicCommand : public Command {
private:
    std::string _channel;
    std::string _topic;

public:
    TopicCommand();
    TopicCommand(const std::string& channel, const std::string& topic);
    TopicCommand(const TopicCommand& other);
    TopicCommand& operator=(const TopicCommand& other);
    ~TopicCommand();

    std::string getTopic() const;
    std::string getChannel() const;
    // std::string getTopic() const;

    void        execute(Server& server, Client& client);
    void        response(Client &client, Server &server);
};
