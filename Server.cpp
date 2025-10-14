#include "Server.hpp"

Server::Server() : _fd(-1), _epoll_fd(-1) {}

Server::~Server() {}

Server::Server(int fd, int epollFd, std::string name, std::string pass)
: _fd(fd), _epoll_fd(epollFd), _name(name), _password(pass) {}

Server::Server(const Server &other) : _fd(other._fd), _epoll_fd(other._epoll_fd), _name(other._name), _password(other._password)
{
	if (this == &other)
		return ;
	*this = other;
}

Server&	Server::operator=(const Server &other)
{
	if (this == &other)
		return (*this);
	this->_sockaddr = other._sockaddr;
	this->_event = other._event;
	for (size_t i = 0; i < this->_clients.size(); i++)
		this->_clients[i] = other._clients[i];
	for (size_t i = 0; i < this->_channels.size(); i++)
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

time_t	Server::getTimestamp() const
{
	return (this->_timestamp);
}

std::vector<Client*>		Server::getClients()
{
	return (this->_clients);
}

std::vector<Channel *>	Server::getChannels()
{
	return (this->_channels);
}

Client*	Server::findClient(const Client * client) const
{
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i] == client)
			return (this->_clients[i]);
	}
	return (NULL);
}

Client*	Server::findClientByNick(std::string clientName) const
{
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_clients[i]->getNickname() == clientName)
			return (this->_clients[i]);
	}
	return (NULL);
}

Client*	Server::findClientByFd(int clientFd) const
{
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_clients[i]->getSocketFd() == clientFd)
			return (this->_clients[i]);
	}
	return (NULL);
}

Channel*	Server::findChannel(const Channel * chan) const
{
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i] == chan)
			return (this->_channels[i]);
	}
	return (NULL);
}

Channel*	Server::findChannelByName(std::string channelName) const
{
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i]->getName() == channelName)
			return (this->_channels[i]);
	}
	return (NULL);
}

void	Server::addClient(Client *client)
{
	// check for duplicates
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i] == client)
			return ;
	}
	this->_clients.push_back(client);
}

void		Server::addChannel(Channel * chan)
{
	// check for duplicates
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i] == chan)
			return ;
	}
	this->_channels.push_back(chan);
}
