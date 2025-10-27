#include "KickCommand.hpp"

KickCommand::KickCommand() : Command("KICK") {}


KickCommand::KickCommand(const std::string& channel, const std::string& target, const std::string& reason)
    : Command("KICK"), _channel(channel), _target(target), _reason(reason) {}

KickCommand::KickCommand(const KickCommand &source) : Command("KICK") {
    *this = source;
}

KickCommand&    KickCommand::operator=(const KickCommand &source) {
    if (this != &source) {
        Command::operator=(source);
        _channel = source._channel;
        _target = source._target;
        _reason = source._reason;
    }
    return *this;
}

KickCommand::~KickCommand() {}


//GETTERS

std::string KickCommand::getChannel() const {
    return _channel;
}

std::string KickCommand::getTarget() const {
    return _target;
}

std::string KickCommand::getReason() const {
    return _reason;
}


// SETTERS

void    KickCommand::setChannel(const std::string& channel) {
    _channel = channel;
}

void    KickCommand::setTarget(const std::string& target) {
    _target = target;
}

void    KickCommand::setReason(const std::string& reason) {
    _reason = reason;
}

//METHODS

////////////////////////////////////////////////////////

Client* KickCommand::findClient(const std::string& client, Channel* channel) {
    std::vector<Client *>   clients = channel->getClients();

    for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++) {
        if ((*it)->getUsername() == client) {
            return *it;
        }
    }
    return NULL;
}

/* Client* KickCommand::findOperator(const std::string& client, Channel* channel) {
    std::vector<Client *>   operators = channel->getOperators();

    for (std::vector<Client *>::iterator it = operators.begin(); it != operators.end(); ++it) {
        if ((*it)->getNickname() == client) {
            return *it;
        }
    }
    return NULL;
} */

////////////////////////////////////////////////////////

void    KickCommand::checkReason() {
    if (_reason.empty()) {
        _reason = "the will of the operator.";
    }
}

//KICK steps:
// 1. Parse: channel, target nickname, optional reason //CHECK
// 2. Verify channel exists //CHECK
// 3. Verify sender is in channel and is operator // CHECK
// 4. Verify target is in channel // CHECK
// 5. Remove target from channel //CHECK
// 6. Broadcast: ":sender KICK #channel target :reason" to all members //CHECK


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
	if (!channel->isClientInChannel(client)) {
// 		ERR_NOTONCHANNEL (442) 
//		"<client> <channel> :You're not on that channel"
		std::string err = client.getUsername() + " " + _channel + " :You're not on that channel\n";
	}
    
    //check whether sender is operator
    if (!channel->isOperator(client)) {
//      ERR_CHANOPRIVSNEEDED (482) 
//      "<client> <channel> :You're not channel operator"
        std::string err = client.getUsername() + " " + _channel + " :You're not channel operator\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return;
    }

    //check whether target is in channel
    Client* target = findClient(_target, channel);
    if (!target) {
//      ERR_USERNOTINCHANNEL (441) 
//      "<client> <nick> <channel> :They aren't on that channel"
        std::string err = client.getUsername() + " " + _target + " " + _channel + " :They aren't on that channel\n";
        send(client.getSocketFd(), err.c_str(), err.length(), 0);
        return;
    }
    
    //broadcast :sender KICK #channel target :reason
    checkReason();
    std::string response = client.getUsername() + " KICK " + _channel + _target + " :" + _reason;
    send(client.getSocketFd(), response.c_str(), response.length(), 0);
    
    //remove target from channel
    channel->removeClient(*target);
    target->removeChannel(channel);

}

void KickCommand::response(Client &client, Server &server)
{
    // TODO: implement
    (void)server;
    (void)client;
}
