#pragma once

#include "headers.hpp"

class Channel;

class Client
{
	private:
		std::string				_nickname;
		epoll_event				_event;
		std::vector<Channel *>	_channels;
		std::string				_username;
		std::string				_hostname;
		std::string				_networkname;
		std::string				_realname;
		std::string				_password;
		int						_socketFd;
		int						_connected;
		int						_channelLimit;
		time_t					_timestamp;

	public:
		Client();
		Client(int fd);
		// Client(std::string nick, int socketFd, epoll_event event);
		Client(const Client &other);
		Client&	operator=(const Client &other);
		~Client();

		static int			totalClientCount;
		static const int	totalClientLimit;

		// std::string	getNickname() const;
		// void	setNickname(std::string nick);
		// int		getSocketFd() const;
		// void	setSocketFd(int fd);
		// epoll_event	getEvent();
		// void	setEvent(struct epoll_event event);
		// int		getConnected();
		// void	setConnected(int status);
		// std::vector<Channel *>	getChannels() const;
		// std::string	getUsername() const;
		// void setUsername(std::string getUsername);
		void 		setHostname(std::string getHostname);
		void 		setNetworkname(std::string getNetworkname);
		void 		setRealname(std::string getRealname);
		void 		setPassword(std::string getPassword);
		void		setNickname(const std::string nick);
		void		setUsername(const std::string username);
		void		setEvent(struct epoll_event event);
		void		setChannels(std::vector<Channel *>);
		void		setSocketFd(int fd);
		void		setConnected(int status);
		void		setChannelLimit(int limit);
		void		setTimestamp(time_t time);

		std::string				getHostname() const;
		std::string				getNetworkname() const;
		std::string				getRealname() const;
		std::string				getPassword() const;
		std::string				getNickname() const;
		std::string				getUsername() const;
		epoll_event				getEvent() const;
		std::vector<Channel *>	getChannels() const;
		int						getSocketFd() const;
		int						getConnected() const;
		int						getChannelLimit() const;
		time_t					getTimestamp() const;

		bool	isInChannel(Channel *channel) const;
		void	addChannel(Channel *channel);
		void	removeChannel(Channel* channel);
};

void	checkConnection(std::string input, Client &client);
