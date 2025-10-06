#pragma once

#include "headers.hpp"

class Client;

class Channel
{
	private:
		std::string	_name;
		std::vector<Client*>	_operators;
		std::string	_password;
		std::string	_topic;
		bool		_i_inviteOnly;
		bool		_t_topicSetable;
		bool		_k_usePassword;
		int			_l_userLimit;
	public:
		Channel();
		~Channel();
		//	Channel(const Channel &other);
		//	Channel& operator=(const Channel &other);
		//	void	_o_givePrivilege(const Client &operator, const Client *target);
		//	void	_o_takePrivilege(const Client &operator, const Client *target);
};
