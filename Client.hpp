#pragma once

#include "headers.hpp"

class Channel;

class Client
{
	private:
		std::string				_nickname;
		std::string				_username; //*
		epoll_event				_event;
		std::vector<Channel *>	_channels;
		int						_socketFd;
		int						_connected;
		int						_channelLimit;
		time_t					_timestamp;
	public:
		Client();
		Client(int fd);
		Client(std::string nick, int socketFd, epoll_event event);
		Client(const Client &other);
		Client&	operator=(const Client &other);
		~Client();

		static int			totalClientCount;
		static const int	totalClientLimit;

		void		setNickname(const std::string nick);
		void		setUsername(const std::string username);
		void		setEvent(struct epoll_event event);
		void		setChannels(std::vector<Channel *>);
		void		setSocketFd(int fd);
		void		setConnected(int status);
		void		setChannelLimit(int limit);
		void		setTimestamp(time_t time);

		std::string				getNickname() const;
		std::string				getUsername() const;
		epoll_event				getEvent();
		std::vector<Channel *>	getChannels();
		int						getSocketFd() const;
		int						getConnected();
		int						getChannelLimit();
		time_t					getTimestamp();

		void	removeChannel(Channel* channel);
		std::vector<Channel *>	getChannels() const;

		void	addChannel(Channel *channel);
		void	removeChannel(Channel *channel);
		bool	isInChannel(Channel *channel) const;
};

void	checkConnection(std::string input, Client &client);
