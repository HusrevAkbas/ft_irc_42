#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

Channel::Channel() : _i_inviteOnly(false), _t_topicSetable(false), _k_usePassword(false), _l_userLimit(0)
{
}

Channel::Channel(const std::string &name) : _name(name), _i_inviteOnly(false), _t_topicSetable(false), _k_usePassword(false), _l_userLimit(0)
{
}

Channel::~Channel() {}

Channel::Channel(const Channel &other)
{
	if (this == &other)
		return ;
	*this = other;
}

Channel&	Channel::operator=(const Channel &other)
{
	if (this == &other)
		return (*this);
	this->_name = other._name;
	this->_operators = other._operators;
	this->_password = other._password;
	this->_topic = other._topic;
	this->_i_inviteOnly = other._i_inviteOnly;
	this->_t_topicSetable = other._t_topicSetable;
	this->_k_usePassword = other._k_usePassword;
	this->_l_userLimit = other._l_userLimit;
	_topicSetterTimestamp = other._topicSetterTimestamp;
	return (*this);
}

std::string	Channel::getName() const
{
	return (this->_name);
}

std::string	Channel::getPass() const
{
	return (this->_password);
}

std::string	Channel::getTopic() const
{
	return (this->_topic);
}

bool	Channel::getInviteStatus() const
{
	return (this->_i_inviteOnly);
}

bool	Channel::getTopicStatus() const
{
	return (this->_t_topicSetable);
}

bool	Channel::getPassStatus() const
{
	return (this->_k_usePassword);
}

int	Channel::getUserLimit() const
{
	return (this->_l_userLimit);
}

std::vector<Client *>	Channel::getOperators() const
{
	return (this->_operators);
}

std::vector<Client *>	Channel::getClients() const
{
	return (this->_clients);
}

std::vector<std::string>	Channel::getInviteList() const {
	return _inviteList;
}

std::pair<std::string, time_t>	Channel::getTopicSetterTimestamp() const {
	return _topicSetterTimestamp;
}

void	Channel::setName(const std::string &name)
{
	this->_name = name;
}

void	Channel::setPassword(const std::string &pass)
{
	this->_password = pass;
}

void	Channel::setTopic(const std::string &topic)
{
	this->_topic = topic;
}

void	Channel::setInviteOnly(bool status)
{
	this->_i_inviteOnly = status;
}

void	Channel::setTopicSetable(bool status)
{
	this->_t_topicSetable = status;
}

void	Channel::setUsePassword(bool status)
{
	this->_k_usePassword = status;
}

void	Channel::setUserLimit(int limit)
{
	this->_l_userLimit = limit;
}

void	Channel::setTopicSetterTimestamp(const std::string& setter, time_t timestamp) {
	_topicSetterTimestamp.first = setter;
	_topicSetterTimestamp.second = timestamp;
}

void	Channel::addClient(Client &client)
{
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i] == &client)
			return;
	}
	this->_clients.push_back(&client);
}

void	Channel::addOperator(Client &client)
{
	for (size_t i = 0; i < this->_operators.size(); i++)
	{
		if (this->_operators[i] == &client)
			return;
	}
	this->_operators.push_back(&client);
}

void	Channel::addInviteList(const std::string& newInvite) {
	if (!isNickInInviteList(newInvite))
		_inviteList.push_back(newInvite);
}

void	Channel::removeClient(Client &client)
{
	for (std::vector<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); ++it)
	{
		if (*it == &client)
		{
			if (isOperator(client))
				removeOperator(client);
			this->_clients.erase(it);
			if (this->getOperators().size() == 0 && this->_clients.size() > 0)
				addOperator(*this->_clients[0]);
			return;
		}
	}
}

void	Channel::removeOperator(Client &client)
{
	for (std::vector<Client *>::iterator it = this->_operators.begin(); it != this->_operators.end(); ++it)
	{
		if (*it == &client)
		{
			this->_operators.erase(it);
			return;
		}
	}
}

bool	Channel::isClientInChannel(Client &client) const
{
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i] == &client)
			return true;
	}
	return false;
}

bool	Channel::isOperator(Client &client) const
{
	for (size_t i = 0; i < this->_operators.size(); i++)
	{
		if (this->_operators[i] == &client)
			return true;
	}
	return false;
}

bool	Channel::isNickInInviteList(const std::string& nickname) {
	for(std::vector<std::string>::iterator it = _inviteList.begin(); it != _inviteList.end(); it++) {
		if (*it == nickname) 
			return true;
	}
	return false;
}


void	Channel::broadcast(Client &client, Server &server, std::string &response)
{
	for (size_t i = 0; i < this->getClients().size(); i++)
	{
		if (this->getClients()[i] != &client)
			server.sendResponse(*this->getClients()[i], response);
	}
}
