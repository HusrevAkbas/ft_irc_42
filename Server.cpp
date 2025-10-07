#include "Server.hpp"

Server::Server() {}

Server::~Server() {}

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
}
