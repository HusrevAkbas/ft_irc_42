#ifndef TOPICCOMMAND_HPP
#define TOPICCOMMAND_HPP

#include "Command.hpp"
#include <string>

class TopicCommand : public Command {
private:
    std::string topic;
    std::string channel;

public:
    TopicCommand(const std::string& chan, const std::string& top);
    virtual ~TopicCommand();

    std::string getTopic() const;
    std::string getChannel() const;
};

#endif
