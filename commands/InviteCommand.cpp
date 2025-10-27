#include "InviteCommand.hpp"

InviteCommand::InviteCommand() : Command("INVITE") {}

InviteCommand::InviteCommand(const std::string& nickname, const std::string& channel)
    : Command("INVITE"), _nickname(nickname), _channel(channel) {}

InviteCommand::InviteCommand(const InviteCommand& other) : Command("INVITE") {
    *this = other;
}

InviteCommand& InviteCommand::operator=(const InviteCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        _nickname = other._nickname;
        _channel = other._channel;
    }
    return *this;
}

InviteCommand::~InviteCommand() {}

std::string InviteCommand::getNickname() const {
    return _nickname;
}

std::string InviteCommand::getChannel() const {
    return _channel;
}


//METHODS

bool    InviteCommand::checkParams(Client& client) {
    if (_nickname.empty()) {
        std::string err = client.getUsername() + " KICK :Not enough parameters\r\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return false;
    }
    if (_channel.empty()) {
        std::string err = client.getUsername() + " KICK :Not enough parameters\r\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return false;
    }
    return true;
}

Client* InviteCommand::findUser(const std::string& nickname, Channel* channel) {
    std::vector<Client *>   clients = channel->getClients();

    for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++) {
        if ((*it)->getNickname() == nickname) {
            return *it;
        }
    }
    return NULL;
}

void    InviteCommand::execute(Server& server, Client& client) {
    //check command parameters
    if (!checkParams(client)) {
        return;
    }

    //check whether channel exists
    Channel* channel = server.findChannelByName(_channel);
    if (!channel) {
        //ERR_NOSUCHCHANNEL (403)
        std::string err = client.getUsername() + " " + _channel + " :No such channel\r\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return;
    }

    //check whether channel is invite-only
    if (channel->getInviteStatus()) {
        //check whether user is operator
        if (!channel->isOperator(client)) {
            //ERR_CHANOPRIVSNEEDED (482)
            std::string err = client.getUsername() + " " + _channel + " :You're not channel operator\r\n";
            send(client.getSocketFd(), err.c_str(), err.length(), 0);
            return;
        }
        //add invite to invite list
        channel->addInviteList(1);
    } else {
        //check whether client is in channel
        if (!channel->isClientInChannel(client)) {
            //ERR_NOTONCHANNEL (442)
            std::string err = client.getUsername() + " " + _channel + " :You're not on that channel\r\n";
            send(client.getSocketFd(), err.c_str(), err.length(), 0);
            return;
        }
    }

    //check whether user is in channel by nickname
    Client* clientB = findUser(_nickname, channel);
    if (!clientB) {
        //ERR_USERONCHANNEL (443)
        std::string err = client.getUsername() + " " + _nickname + " " + _channel + " :is already on channel\r\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return;
    }

    //send invite to user
    std::string response = client.getUsername() + " invites you to #" + _channel + "\r\n";
    send(clientB->getSocketFd(), response.c_str(), response.length(), 0);
}

void InviteCommand::response(Client &client, Server &server)
{
    // TODO: implement
    // (void)server;
    // (void)client;
    execute(server, client);
}
