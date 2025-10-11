#pragma once

#include "headers.hpp"
#include "Client.hpp"
#include "Channel.hpp"

#define	MAX_CLIENTS		1000
#define	MAX_CHANNELS	100

class Server
{
	private:
		int			_fd;
		int			_epoll_fd;
		std::string	_name;
		std::string	_password;
		sockaddr_in	_sockaddr;
		epoll_event	_event;
		Client		_clients[MAX_CLIENTS];
		Channel		_channels[MAX_CHANNELS];
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
		Client*		getClients();
		Channel*	getChannels();

		//CHOOSE ONE METHOD
		// 1- return pointer and NULL if dont find
		// 2- return reference and throw error if dont find
		Client	&findClientByNick(std::string clientName);
		Client	&findClientByFd(int clientFd);
		Channel	&findChannelByName(std::string channelName);
};
