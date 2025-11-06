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
        std::string err = ": " + server.getName() + " 403 " + client.getNickname() + " " + _channel + " :No such channel\r\n";
        server.sendResponse(client, err);
        return;
    }

    //check whether client is in channel
    if (!channel->isClientInChannel(client)) {
        //ERR_NOTONCHANNEL (442)
        std::string err = ": " + server.getName() + " 442 " + client.getNickname() + " " + _channel + " :You're not on that channel\r\n";
        server.sendResponse(client, err);
        return;
    }

    //VIEW
    if (_topic.empty()) {
        //check for topic
        std::string topic = channel->getTopic();
        if (topic.empty()) {
            //RPL_NOTOPIC (331)
            std::string response = ": " + server.getName() + " 331 " + client.getNickname() + " " + _channel + " :No topic is set\r\n";
            server.sendResponse(client, response);
            return;
        } else {
            //RPL_TOPIC (332)
            std::string response = ": " + server.getName() + " 332 " + client.getNickname() + " " + _channel + " :<" + topic + ">\r\n";
            server.sendResponse(client, response);
            //RPL_TOPICWHOTIME (333) 
            std::pair<std::string, time_t>  st = channel->getTopicSetterTimestamp();
            response = ": " + server.getName() + " 333 " + client.getNickname() + " " + _channel + " " + st.first + " " + ctime(&st.second) + "\r\n";
            server.sendResponse(client, response);
            return;
        }
    }

    //CHANGE

    //check protected topic mode
    if (channel->getTopicStatus()) {
        //check client is operator
        if (!channel->isOperator(client)) {
            //ERR_CHANOPRIVSNEEDED (482)
            std::string err = ": " + server.getName() + " 482 " + client.getNickname() + " " + _channel + " :You're not channel operator\r\n";
            server.sendResponse(client, err);
            return;
        }
    }

    //clear topic
    if (_topic == "") {
        channel->setTopic(_topic);
        channel->setTopicSetterTimestamp(client.getNickname(), time(0));
        std::string response = ": " + server.getName() + " 332 " + client.getNickname() + " " + _channel + " :< >\r\n";
        server.sendResponse(client, response);
    }

    //change topic
    channel->setTopic(_topic);
    channel->setTopicSetterTimestamp(client.getNickname(), time(0));
    std::string response = Command::buildNumericReplyNoColon(server, client, RPL_TOPIC, channel->getName(), channel->getTopic());
    server.sendResponse(client, response);
    channel->broadcast(client, server, response);
}

void TopicCommand::response(Client &client, Server &server)
{
    execute(server, client);
}
