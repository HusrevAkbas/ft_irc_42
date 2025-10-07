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
	this->_clients = other._clients;
	this->_channels = other._channels;
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
