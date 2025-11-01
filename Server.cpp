#include "Server.hpp"

Server::Server() : _fd(-1), _epoll_fd(-1) {}

Server::~Server()
{
	for (std::vector<Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		close ((*it)->getSocketFd());
		delete *it;
	}
	for (std::vector<Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++)
		delete *it;
}

Server::Server(int fd, int epollFd, std::string name, std::string pass, sockaddr_in addr)
: _fd(fd), _epoll_fd(epollFd), _name(name), _password(pass), _sockaddr(addr)
{
	this->_timestamp = time(NULL);
}

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
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i] == client)
			return (this->_clients.begin() + i);
	}
	return (this->_clients.end());
}

Client*	Server::findClientByNick(std::string clientName) const
{
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i]->getNickname() == clientName)
			return (this->_clients[i]);
	}
	return (NULL);
}

Client*	Server::findClientByFd(int clientFd) const
{
	for (size_t i = 0; i < this->_clients.size(); i++)
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

	if (!client)
	{
		std::cout << "Client NOT found\n";
		return ;
	}

	// be sure client exist in list
	pos = this->findClientPos(client);
	if (pos != this->_clients.end())
	{
		close(client->getSocketFd());
		delete (*pos);
		this->_clients.erase(pos);
	}
}

void	Server::removeChannel(Channel * channel)
{
	std::vector<Channel *>::iterator	pos;

	pos = this->findChannelPos(channel);
	if (pos != this->_channels.end())
	{
		delete (*pos);
		this->_channels.erase(pos);
	}
}

void	Server::handleRequest(std::string input, int fd)
{
	std::stringstream	ss(input);
	std::string	request;

	// client may send many request at once, divide requests then process
	while (std::getline(ss, request))
	{
		request += "\n";
		// TODO: output for development, testing and debugging, REMOVE after project is ready
		std::cout << GREEN << "---REQUEST---: " << RESET << request;
		try
		{
			Command	*command = parseCommand(request);
			Client	*client = findClientByFd(fd);
			std::string	response;
			
			// let command class handle request and then send response
			command->response(*client, *this);
		}
		catch (std::exception &e)
		{
			// TODO: output for development, testing and debugging, REMOVE after project is ready
			std::cerr << "Exception catched in Server::handleRequest:\n" << e.what() << "\n";
		}
	}
}

void Server::sendResponse(Client &client, const std::string& response)
{
	std::cout << YELLOW << "---RESPONSE---: " << RESET << response;
	send(client.getSocketFd(), response.c_str(), response.length(), 0);
}

void	Server::broadcast(Client &client, std::string response)
{
	for (size_t i = 0; i < this->getClients().size(); i++)
	{
		if (this->getClients()[i] != &client)
			this->sendResponse(*this->getClients()[i], response);
	}
}

const char*	Server::ClientLimitReachedException::what() const throw ()
{
	return ("ServerException: Client limit reached");
}

const char*	Server::ChannelLimitReachedException::what() const throw ()
{
	return ("ServerException: Channel limit reached");
}

std::ostream&	operator<<(std::ostream& o, Server &server)
{
	time_t	time = server.getTimestamp();
	o << "Server name: " << server.getName() << "\n"
	<< "Password: " << server.getPass() << "\n"
	<< "Ip: " << inet_ntoa(server.getAddr().sin_addr) << "\n"
	<< "Port: " << ntohs(server.getAddr().sin_port) << "\n"
	<< "Created at: " << ctime(&time)
	<< "Number of Clients: " << server.getClients().size() << "\n";
	for (size_t i = 0; i < server.getClients().size(); i++)
	{
		o << "\t" << i << ": " << server.getClients()[i]->getNickname() << " "
		<< server.getClients()[i]->getSocketFd() << "\n";
	}
	o << "Number of Channels: " << server.getChannels().size() << "\n";
	for (size_t i = 0; i < server.getChannels().size(); i++)
	{
		o << "\t" << i << ": " << server.getChannels()[i]->getName() << "\n";
	}
	return (o);
}
