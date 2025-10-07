#pragma once

#include "headers.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Server
{
	private:
		int			_fd;
		int			_epoll_fd;
		std::string	_name;
		std::string	_password;
		sockaddr_in	_sockaddr;
		epoll_event	_event;
		std::vector<Client>	_clients;
		std::vector<Channel>	_channels;
	public:
		Server();
		~Server();
		Server(const Server &other);
		Server&	operator=(const Server &other);
};
