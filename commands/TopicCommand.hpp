#ifndef TOPICCOMMAND_HPP
#define TOPICCOMMAND_HPP

#include "Command.hpp"
#include <string>

class TopicCommand : public Command {
private:
    std::string channel;
    std::string topic;

public:
    TopicCommand(const std::string& chan, const std::string& top);
    virtual ~TopicCommand();

    std::string getChannel() const;
    std::string getTopic() const;
};

#endif
