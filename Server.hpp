#pragma once

#include "headers.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "commands/Command.hpp"

#define	MAX_CLIENTS		1000
#define	MAX_CHANNELS	100
#define SERVER_NAME		"ircserv42"

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
		std::string	err_msg;
	public:
		Server();
		~Server();
		Server(const Server &other);
		Server&	operator=(const Server &other);
		Server(int fd, int epollFd, std::string name, std::string pass, sockaddr_in addr);

		int	getFd();
		int	getEpollFd();
		std::string	getName() const;
		std::string	getPass() const;
		sockaddr_in	getAddr() const;
		epoll_event	getEvent() const;
		time_t		getTimestamp() const;
		std::vector<Client*>	getClients();
		std::vector<Channel*>	getChannels();

		std::vector<Client *>::iterator	findClientPos(const Client * client);
		Client*		findClientByNick(std::string clientName) const;
		Client*		findClientByFd(int clientFd) const;
		std::vector<Channel*>::iterator	findChannelPos(const Channel * channel);
		Channel*	findChannelByName(std::string channelName) const;

		void		addClient(Client * client);
		void		addChannel(Channel * channel);

		void		removeClient(Client * client);
		void		removeChannel(Channel * channel);

		void	handleRequest(std::string request, int fd);
		void	sendResponse(Client &client, const std::string& response);
		void	broadcast(Client &client, std::string message);

		class ClientLimitReachedException: public std::exception
		{	const char *what () const throw ();	};
		class ChannelLimitReachedException: public std::exception
		{	const char *what () const throw ();	};
};

std::ostream&	operator<<(std::ostream& o, Server &server);

Command* parseCommand(const std::string& input);