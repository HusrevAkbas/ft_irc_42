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

std::vector<Client *>::iterator	Server::findClientPos(const Client * client)
{
	return this->_clients.begin();

	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i] == client)
			return (this->_clients.begin() + i);
	}
	return (this->_clients.end());
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

std::vector<Channel*>::iterator	Server::findChannelPos(const Channel * chan)
{
	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i] == chan)
			return (this->_channels.begin() + i);
	}
	return (this->_channels.end());
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

/*
	Adds client to list
	check limits before calling this function
*/
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

/*
	Adds channel to list
	check limits before calling this function
*/
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

void	Server::removeClient(Client * client)
{
	std::vector<Client *>::iterator	pos;

	// be sure client exist in list
	pos = this->findClientPos(client);
	if (pos != this->_clients.end())
	{
		close(client->getSocketFd());
		this->_clients.erase(pos);
	}
}

void	Server::removeChannel(Channel * channel)
{
	std::vector<Channel *>::iterator	pos;

	pos = this->findChannelPos(channel);
	if (pos != this->_channels.end())
		this->_channels.erase(pos);
}

const char*	Server::ClientLimitReachedException::what() const throw ()
{
	return ("ServerException: Client limit reached");
}

const char*	Server::ChannelLimitReachedException::what() const throw ()
{
	return ("ServerException: Channel limit reached");
}
