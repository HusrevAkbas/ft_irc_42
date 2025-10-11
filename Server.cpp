#include "Server.hpp"

Server::Server() {}

Server::~Server() {}

Server::Server(int fd, int epollFd, std::string name, std::string pass)
: _fd(fd), _epoll_fd(epollFd), _name(name), _password(pass) {}

Server::Server(const Server &other)
{
	if (this == &other)
		return ;
	*this = other;
}

Server&	Server::operator=(const Server &other)
{
	if (this == &other)
		return (*this);
	this->_fd = other._fd;
	this->_epoll_fd = other._epoll_fd;
	this->_name = other._name;
	this->_password = other._password;
	this->_sockaddr = other._sockaddr;
	this->_event = other._event;
	for (size_t i = 0; i < MAX_CLIENTS; i++)
		this->_clients[i] = other._clients[i];
	for (size_t i = 0; i < MAX_CLIENTS; i++)
		this->_channels[i] = other._channels[i];
	return (*this);
}

int	Server::getFd()
{
	return (this->_fd);
}

int	Server::getEpollFd()
{
	return (this->_epoll_fd);
}

std::string	Server::getName() const
{
	return (this->_name);
}

std::string	Server::getPass() const
{
	return (this->_password);
}

sockaddr_in	Server::getAddr() const
{
	return (this->_sockaddr);
}

epoll_event	Server::getEvent() const
{
	return (this->_event);
}
Client*		Server::getClients()
{
	return (this->_clients);
}
Channel*	Server::getChannels()
{
	return (this->_channels);
}

Client	&Server::findClientByNick(std::string clientName)
{
	for (size_t i = 0; i < MAX_CLIENTS; i++)
	{
		if (this->_clients[i].getNickname() == clientName)
			return (this->_clients[i]);
	}
	throw std::invalid_argument("Client not found");
}

Client	&Server::findClientByFd(int clientFd)
{
	for (size_t i = 0; i < MAX_CLIENTS; i++)
	{
		if (this->_clients[i].getSocketFd() == clientFd)
			return (this->_clients[i]);
	}
	throw std::invalid_argument("Client not found");
}

Channel	&Server::findChannelByName(std::string channelName)
{
	for (size_t i = 0; i < MAX_CHANNELS; i++)
	{
		if (this->_channels[i].getName() == channelName)
			return (this->_channels[i]);
	}
	throw std::invalid_argument("Channel not found");
}
