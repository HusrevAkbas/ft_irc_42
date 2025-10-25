#include "KickCommand.hpp"

KickCommand::KickCommand() {} //default constructor is needed for Command class

KickCommand::KickCommand(const std::string& channel, const std::string& target, const std::string& reason)
    : Command("KICK"), _channel(channel), _target(target), _reason(reason) {}

KickCommand::KickCommand(const KickCommand &source) {
    *this = source;
}

KickCommand&    KickCommand::operator=(const KickCommand &source) {
    if (this != &source)
}

KickCommand::~KickCommand() {}

std::string KickCommand::getChannel() const {
    return _channel;
}

std::string KickCommand::getTarget() const {
    return _target;
}

std::string KickCommand::getReason() const {
    return _reason;
}

void    KickCommand::setChannel(const std::string& channel) {
    _channel = channel;
}

void    KickCommand::setTarget(const std::string& target) {
    _target = target;
}

void    KickCommand::setReason(const std::string& reason) {
    _reason = reason;
}

//KICK steps:
// 1. Parse: channel, target nickname, optional reason //CHECK
// 2. Verify channel exists //CHECK
// 3. Verify sender is in channel and is operator // CHECK
// 4. Verify target is in channel // CHECK
// 5. Remove target from channel
// 6. Broadcast: ":sender KICK #channel target :reason" to all members

Client* KickCommand::findClient(const std::string& client, Channel* channel) {
    std::vector<Client *>   clients = channel->getClients();

    for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++) {
        if ((*it)->getNickname() == client) {
            return *it;
        }
    }
    return NULL;
}

Client* KickCommand::findOperator(const std::string& client, Channel* channel) {
    std::vector<Client *>   operators = channel->getOperators();

    for (std::vector<Client *>::iterator it = operators.begin(); it != operators.end(); ++it) {
        if ((*it)->getNickname() == client) {
            return *it;
        }
    }
    return NULL;
}

void    KickCommand::execute(Server& server, Client& client) {
    //check whether channel exists
    Channel* channel = server.findChannelByName(_channel);
    if (!channel) {
//      ERR_NOSUCHCHANNEL (403) 
//      "<client> <channel> :No such channel"
        std::string err = client.getUsername() + " " + _channel + " :No such channel\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return; 
    }

	//check whether sender is in channel
	if (!findClient(client.getNickname(), channel)) {
// 		ERR_NOTONCHANNEL (442) 
//		"<client> <channel> :You're not on that channel"
		std::string err = client.getUsername() + " " + _channel + " :You're not on that channel\n";
	}
    
    //check whether sender is operator
    if (!findOperator(client.getNickname(), channel)) {
//      ERR_CHANOPRIVSNEEDED (482) 
//      "<client> <channel> :You're not channel operator"
        std::string err = client.getUsername() + " " + _channel + " :You're not channel operator\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return;
    }

    //check whether target is in channel
    if (!findClient(_target, channel)) {
//      ERR_USERNOTINCHANNEL (441) 
//      "<client> <nick> <channel> :They aren't on that channel"
        std::string err = client.getUsername() + " " + _target + " " + _channel + " :They aren't on that channel\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return;
    }

}