#pragma once

#include "headers.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#define	MAX_CLIENTS		1000
#define	MAX_CHANNELS	100

/*
	NOTES:
		- clients and channels will be created by new keyword and
			pointers will be stored in vectors
*/

class Server
{
	private:
		const int	_fd;
		const int	_epoll_fd;
		const std::string	_name;
		const std::string	_password;
		sockaddr_in	_sockaddr;
		epoll_event	_event;
		std::vector<Client *>	_clients;
		std::vector<Channel *>	_channels;
		time_t		_timestamp;
	public:
		Server();
		~Server();
		Server(const Server &other);
		Server&	operator=(const Server &other);
		Server(int fd, int epollFd, std::string name, std::string pass);

		int	getFd();
		int	getEpollFd();
		std::string	getName() const;
		std::string	getPass() const;
		sockaddr_in	getAddr() const;
		epoll_event	getEvent() const;
		time_t		getTimestamp() const;
		std::vector<Client*>	getClients();
		std::vector<Channel*>	getChannels();

		Client*		findClient(const Client * client) const;
		Client*		findClientByNick(std::string clientName) const;
		Client*		findClientByFd(int clientFd) const;
		Channel*	findChannel(const Channel * channel) const;
		Channel*	findChannelByName(std::string channelName) const;

		void		addClient(Client *);
		 void		addChannel(Channel *);
};
