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
}
