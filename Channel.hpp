#pragma once

#include "headers.hpp"

class Client;

class Channel
{
	private:
		std::string	_name;
		std::vector<Client *>	_operators;
		std::vector<Client *>	_clients;
		std::string	_password;
		std::string	_topic;
		bool		_i_inviteOnly;
		bool		_t_topicSetable;
		bool		_k_usePassword;
		int			_l_userLimit;
		time_t		_timestamp;
	public:
		Channel();
		~Channel();
		Channel(const Channel &other);
		Channel& operator=(const Channel &other);
		//	void	_o_givePrivilege(const Client &operator, const Client *target);
		//	void	_o_takePrivilege(const Client &operator, const Client *target);

		static int			totalChannelCount;
		static const int	totalChannelLimit;

		std::string	getName() const;
		std::string	getPass() const;
		std::string	getTopic() const;
		bool	getInviteStatus() const;
		bool	getTopicStatus() const;
		bool	getPassStatus() const;
		int		getUserLimit() const;
		std::vector<Client *>	getOperators() const;
		std::vector<Client *>	getClients() const;
};
