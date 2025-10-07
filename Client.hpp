#pragma once

#include "headers.hpp"

class Channel;

class Client
{
	private:
		std::string	_nickname;
		int			_socketFd;
		epoll_event	_event;
		int			_connected;
		std::vector<Channel *>	_channels;
	public:
		Client();
		Client(std::string nick, int socketFd);
		~Client();
		Client(const Client &other);
		Client&	operator=(const Client &other);

		std::string	getNickname() const;
		void	setNickname(std::string nick);
		int		getSocketFd() const;
		void	setSocketFd(int fd);
		epoll_event	getEvent();
		void	setEvent(struct epoll_event event);
		int		getConnected();
		void	setConnected(int status);
};

void	checkConnection(std::string input, Client &client);
