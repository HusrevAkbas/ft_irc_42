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
	this->_socketFd = other._socketFd;
	this->_event = other._event;
	this->_connected = other._connected;
	this->_channels = other._channels;
	return (*this);
}

int	Client::totalClientCount = 0;
const int	Client::totalClientLimit = 1000;

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

std::vector<Channel *>	Client::getChannels() const
{	return (this->_channels);	}

std::string	Client::getUsername() const
{	return (this->_username);	}

std::string	Client::getHostname() const
{	return (this->_hostname);	}

std::string	Client::getNetworkname() const
{	return (this->_networkname);	}

std::string	Client::getRealname() const
{	return (this->_realname);	}

std::string	Client::getPassword() const
{	return (this->_password);	}

void	Client::setUsername(std::string username)
{
	this->_username = username;
}
void	Client::setHostname(std::string hostname)
{
	this->_hostname = hostname;
}
void	Client::setNetworkname(std::string networkname)
{
	this->_networkname = networkname;
}
void	Client::setRealname(std::string realname)
{
	this->_realname = realname;
}
void	Client::setPassword(std::string password)
{
	this->_password = password;
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

void	Client::removeChannel(Channel *channel)
{
	if (!channel)
		return;

	for (std::vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it)
	{
		if (*it == channel)
		{
			this->_channels.erase(it);
			return;
		}
	}
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
