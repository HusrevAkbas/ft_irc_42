#include "TopicCommand.hpp"

TopicCommand::TopicCommand() : Command("TOPIC") {}

TopicCommand::TopicCommand(const std::string& chan, const std::string& top)
    : Command("TOPIC"), channel(chan), topic(top) {}

TopicCommand::TopicCommand(const TopicCommand& other) : Command("TOPIC") {
    *this = other;
}

TopicCommand& TopicCommand::operator=(const TopicCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        channel = other.channel;
        topic = other.topic;
    }
    return *this;
}

TopicCommand::~TopicCommand() {}

std::string TopicCommand::getChannel() const {
    return channel;
}

std::string TopicCommand::getTopic() const {
    return topic;
}

void TopicCommand::response(Client &client, Server &server)
{
    // TODO: implement
    (void)server;
    (void)client;
}
