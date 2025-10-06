#include "TopicCommand.hpp"

TopicCommand::TopicCommand(const std::string& chan, const std::string& top)
    : Command("TOPIC"), channel(chan), topic(top) {}

TopicCommand::~TopicCommand() {}

std::string TopicCommand::getChannel() const {
    return channel;
}

std::string TopicCommand::getTopic() const {
    return topic;
}
