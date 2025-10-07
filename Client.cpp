#include "Client.hpp"

Client::Client() : _socketFd(-1) {}

Client::Client(int fd) : _socketFd(fd) {}

Client::Client(std::string nick, int fd, epoll_event event) : _nickname(nick), _socketFd(fd), _event(event) {}

Client::~Client() {}

Client::Client(const Client &other)
{
	if (this == &other)
		return ;
	*this = other;
}

Client&	Client::operator=(const Client &other)
{
	if (this == &other)
		return (*this);
	this->_nickname = other._nickname;
	this->_socketFd = other._socketFd;
	this->_event = other._event;
	this->_connected = other._connected;
	this->_channels = other._channels;
	return (*this);
}

std::string	Client::getNickname() const
{	return (this->_nickname);	}

int	Client::getSocketFd() const
{	return (this->_socketFd);	}

void	Client::setSocketFd(int fd)
{	this->_socketFd = fd;	}

void	Client::setNickname(std::string nick)
{	this->_nickname = nick;	}

epoll_event	Client::getEvent()
{	return (this->_event);	}

void	Client::setEvent(struct epoll_event event)
{	this->_event = event;	}

int	Client::getConnected()
{	return (this->_connected);	}

void	Client::setConnected(int status)
{	this->_connected = status;	}
