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
		std::string	_username;
		std::string	_hostname;
		std::string	_networkname;
		std::string	_realname;
		std::string	_password;

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
		std::vector<Channel *>	getChannels() const;
		std::string	getUsername() const;
		std::string	getHostname() const;
		std::string	getNetworkname() const;
		std::string	getRealname() const;
		std::string	getPassword() const;
		void setUsername(std::string getUsername);
		void setHostname(std::string getHostname);
		void setNetworkname(std::string getNetworkname);
		void setRealname(std::string getRealname);
		void setPassword(std::string getPassword);

		void	addChannel(Channel *channel);
		void	removeChannel(Channel *channel);
		bool	isInChannel(Channel *channel) const;
};

void	checkConnection(std::string input, Client &client);
