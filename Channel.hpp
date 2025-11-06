#pragma once

#include "headers.hpp"

class Client;
class Server;

class Channel
{
	private:
		std::string	_name;
		std::vector<Client *>			_operators;
		std::vector<Client *>			_clients;
		std::vector<std::string>		_inviteList;
		std::pair<std::string, time_t>	_topicSetterTimestamp;
		std::string	_password;
		std::string	_topic;
		bool		_i_inviteOnly;
		bool		_t_topicSetable;
		bool		_k_usePassword;
		int			_l_userLimit;
		time_t		_timestamp;
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
		std::vector<Client *>			getOperators() const;
		std::vector<Client *>			getClients() const;
		std::vector<std::string>		getInviteList() const;
		std::pair<std::string, time_t>	getTopicSetterTimestamp() const;

		void	setName(const std::string &name);
		void	setPassword(const std::string &pass);
		void	setTopic(const std::string &topic);
		void	setInviteOnly(bool status);
		void	setTopicSetable(bool status);
		void	setUsePassword(bool status);
		void	setUserLimit(int limit);
		void	setTopicSetterTimestamp(const std::string& setter, time_t timestamp);

		void	addClient(Client &client);
		void	addOperator(Client &client);
		void	addInviteList(const std::string& newInvite);
		void	removeClient(Client &client);
		void	removeOperator(Client &client);
		bool	isClientInChannel(Client &client) const;
		bool	isOperator(Client &client) const;
		bool	isNickInInviteList(const std::string& nickname);

		void	broadcast(Client &client, Server &server, std::string &response);
};
