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

//GETTERS

std::string InviteCommand::getNickname() const {
    return _nickname;
}

std::string InviteCommand::getChannel() const {
    return _channel;
}


//METHODS

bool    InviteCommand::checkParams(Server& server, Client& client) {
    if (_nickname.empty()) {
        std::string err = client.getNickname() + " KICK :Not enough parameters\r\n";
        server.sendResponse(client, err);
        return false;
    }
    if (_channel.empty()) {
        std::string err = client.getNickname() + " KICK :Not enough parameters\r\n";
        server.sendResponse(client, err);
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
    if (!checkParams(server, client)) {
        return;
    }

    //check whether channel exists
    Channel* channel = server.findChannelByName(_channel);
    if (!channel) {
        //ERR_NOSUCHCHANNEL (403)
        std::string err = ":" + server.getName() + " 403 " + client.getNickname() + " " + _channel + " :No such channel\r\n";
        server.sendResponse(client, err);
        return;
    }

    //check whether target exists
    if (!server.findClientByNick(_nickname)){
        //ERR_NOSUCHNICK (401)
        std::string err = ":" + server.getName() + " 401 " + client.getNickname() + " " + _nickname + " :No such nick\r\n";
        server.sendResponse(client, err);
        return ;
    }

    //check whether channel is invite-only
    if (channel->getInviteStatus()) {
        //check whether user is operator
        if (!channel->isOperator(client)) {
            //ERR_CHANOPRIVSNEEDED (482)
            std::string err = ":" + server.getName() + " 482 " + client.getNickname() + " " + _channel + " :You're not channel operator\r\n";
            server.sendResponse(client, err);
            return;
        }
        //add invite to invite list
        channel->addInviteList(_nickname);
    } else {
        //check whether client is in channel
        if (!channel->isClientInChannel(client)) {
            //ERR_NOTONCHANNEL (442)
            std::string err = ":" + server.getName() + " 442 " + client.getNickname() + " " + _channel + " :You're not on that channel\r\n";
            server.sendResponse(client, err);
            return;
        }
    }

    //check whether user is in channel by nickname
    Client* clientB = findUser(_nickname, channel);
    if (clientB) {
        //ERR_USERONCHANNEL (443)
        std::string err = ":" + server.getName() + " 443 " + client.getNickname() + " " + _nickname + " " + _channel + " :is already on channel\r\n";
        server.sendResponse(client, err);
        return;
    }

    //send invite to user
    std::string response = ":" + server.getName() + " 341 " + client.getNickname() + " " + _nickname + " " + _channel + "\r\n";
    server.sendResponse(*clientB, response);
}

void InviteCommand::response(Client &client, Server &server)
{
    execute(server, client);
}
