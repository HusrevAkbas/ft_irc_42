#include "Channel.hpp"

Channel::Channel() {}

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
	return (*this);
}

int			Channel::totalChannelCount = 0;
const int	Channel::totalChannelLimit = 100;

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