#include "Client.hpp"
#include "Channel.hpp"

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
	this->_username = other._username;
	this->_event = other._event;
	this->_channels = other._channels;
	this->_socketFd = other._socketFd;
	this->_connected = other._connected;
	this->_channelLimit = other._channelLimit;
	this->_timestamp = other._timestamp;
	return (*this);
}

int	Client::totalClientCount = 0;
const int	Client::totalClientLimit = 1000;


//GETTERS

std::string	Client::getNickname() const
{	return (this->_nickname);	}

std::string	Client::getUsername() const
{	return (this->_username);	}

epoll_event	Client::getEvent()
{	return (this->_event);	}

std::vector<Channel *>	Client::getChannels() {
	return _channels;
}

int	Client::getSocketFd() const
{	return (this->_socketFd);	}

int	Client::getConnected()
{	return (this->_connected);	}

int	Client::getChannelLimit() {
	return _channelLimit;
}

time_t	Client::getTimestamp() {
	return _timestamp;
}


//SETTERS

void	Client::setNickname(const std::string nick)
{	this->_nickname = nick;	}

void	Client::setUsername(const std::string username)
{	this->_username = username;	}

void	Client::setEvent(struct epoll_event event)
{	this->_event = event;	}

void	Client::setChannels(std::vector<Channel *> channels) {
	_channels = channels;
}

void	Client::setSocketFd(int fd)
{	this->_socketFd = fd;	}

void	Client::setConnected(int status)
{	this->_connected = status;	}


void	Client::setChannelLimit(int limit) {
	_channelLimit = limit;
}

void	Client::setTimestamp(time_t time) {
	_timestamp = time;
}


bool	Client::isInChannel(Channel *channel) const
{
	if (!channel)
		return false;

	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i] == channel)
			return true;
	}
	return false;
}

void	Client::addChannel(Channel *channel)
{
	if (!channel)
		return;

	for (size_t i = 0; i < this->_channels.size(); i++)
	{
		if (this->_channels[i] == channel)
			return;
	}
	this->_channels.push_back(channel);
}


void	Client::removeChannel(Channel* channel) {
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		if (*it == channel) {
			_channels.erase(it);
			break;
		}
	}
}