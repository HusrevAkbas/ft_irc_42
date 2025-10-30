#include "TopicCommand.hpp"

TopicCommand::TopicCommand() : Command("TOPIC") {}

TopicCommand::TopicCommand(const std::string& channel, const std::string& topic)
    : Command("TOPIC"), _channel(channel), _topic(topic) {}

TopicCommand::TopicCommand(const TopicCommand& other) : Command("TOPIC") {
    *this = other;
}

TopicCommand& TopicCommand::operator=(const TopicCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        _channel = other._channel;
        _topic = other._topic;
    }
    return *this;
}

TopicCommand::~TopicCommand() {}

std::string TopicCommand::getChannel() const {
    return _channel;
}

std::string TopicCommand::getTopic() const {
    return _topic;
}


//METHODS

void    TopicCommand::execute(Server& server, Client& client) {
    //check whether channel exists
    Channel* channel = server.findChannelByName(_channel);
    if (!channel) {
        //ERR_NOSUCHCHANNEL (403)
        std::string err = client.getUsername() + " " + _channel + " :No such channel\r\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return;
    }

    //check whether client is in channel
    if (!channel->isClientInChannel(client)) {
        //ERR_NOTONCHANNEL (442)
        std::string err = client.getUsername() + " " + _channel + " :You're not on that channel\r\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return;
    }

    //VIEW
    if (_topic.empty()) {
        //check for topic
        std::string topic = channel->getTopic();
        if (topic.empty()) {
            //RPL_NOTOPIC (331)
            std::string response = client.getUsername() + " " + _channel + " :No topic is set\r\n";
            send(client.getSocketFd(), response.c_str(), response.length(), 0);
            return;
        } else {
            //RPL_TOPIC (332)
            std::string response = client.getUsername() + " " + _channel + " :<" + topic + ">\r\n";
            send(client.getSocketFd(), response.c_str(), response.length(), 0);
            //TO-DO add whotime 
            return;
        }
    }

    //CHANGE

    //check protected topic mode
    if (channel->getTopicStatus()) {
        //check client is operator
        if (!channel->isOperator(client)) {
            std::string err = client.getUsername() + " " + _channel + " :You're not channel operator\r\n";
            send(client.getSocketFd(), err.c_str(), err.length(), 0);
            return;
        }
    }

    //clear topic
    if (_topic == "") {
        channel->setTopic(_topic);
    }

    //change topic
    channel->setTopic(_topic);
    std::string response = Command::buildNumericReplyNoColon(server, client, RPL_TOPIC, channel->getName(), channel->getTopic());
    server.sendResponse(client, response);
}

void TopicCommand::response(Client &client, Server &server)
{
    // TODO: implement
    // (void)server;
    // (void)client;
    execute(server, client);
}
