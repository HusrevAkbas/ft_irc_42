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
		int			_channelLimit;
		time_t		_timestamp;
	public:
		Client();
		Client(int fd);
		Client(std::string nick, int socketFd, epoll_event event);
		~Client();
		Client(const Client &other);
		Client&	operator=(const Client &other);

		static int			totalClientCount;
		static const int	totalClientLimit;

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
