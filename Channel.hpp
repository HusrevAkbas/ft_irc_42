#pragma once

#include "headers.hpp"

class Client;
class Server;

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
		int			_inviteList;
	public:
		Channel();
		Channel(const std::string &name);
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
		int		getInviteList() const;

		void	setName(const std::string &name);
		void	setPassword(const std::string &pass);
		void	setTopic(const std::string &topic);
		void	setInviteOnly(bool status);
		void	setTopicSetable(bool status);
		void	setUsePassword(bool status);
		void	setUserLimit(int limit);

		void	addClient(Client &client);
		void	addOperator(Client &client);
		void	addInviteList(int newInvite);
		void	removeClient(Client &client);
		void	removeOperator(Client &client);
		bool	isClientInChannel(Client &client) const;
		bool	isOperator(Client &client) const;

		void	broadcast(Client &client, Server &server, std::string &response);
};
