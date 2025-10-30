#include "Server.hpp"
#include <string>
#include <sstream>

#define	BUFFER_SIZE	1000
#define	MAX_READY_EVENTS	100

bool	isArgValid(int argc, char** argv, std::string &password, int &port)
{
	std::stringstream	ss;
	std::string			str_port;

	// argument count
	if (argc != 3)
	{
		std::cerr << "Program takes exatly 3 arguments\n./ircserv [port] [password]\n";
		return (false);
	}

	// validate port
	str_port = argv[1];
	if (str_port.find_first_not_of("1234567890") != std::string::npos)
	{
		std::cerr << "Error: invalid char in PORT argument: " << str_port[str_port.find_first_not_of("1234567890")] << "\n";
		return (false);
	}
	ss.str(str_port);
	ss >> port;
	if (port < 0 || port > 65535)
	{
		std::cerr << "Error: invalid port number.\n"
		<<"\t- Port variable uses unsigned short int (2 bytes).\n\t- Usable range is [0 - 65535]\n";
		return (false);
	}
	// check if password has only ascii printable characters
	password = argv[2];
	for (size_t i = 0; i < password.length(); i++)
	{
		if (!isprint(password[i]))
		{
			std::cerr << "Error: invalid password, only ascii printable characters are supported\n";
			return (false);
		}
	}
	return (true);
}

int	main(int argc, char **argv)
{
	std::string	password;
	int			port;

	if (!isArgValid(argc, argv, password, port))
		return (0);

	int	server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_socket_fd == -1)
	{
		std::cerr << "Error: socket";
		return (1);
	}

	// SO_REUSEADDR allow to use same port immediately,
	// otherwise port goes into TIME_WAIT status to consume remaining data in socket
	int	opt = 1;
	if (setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		std::cerr << "Error: setsockopt " << opt << "\n";
		return (1);
	}

	//	assign an address to server socket
	sockaddr_in	server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//	bind server socket and address
	if (bind(server_socket_fd, (sockaddr *) &server_address, sizeof(server_address)))
	{
		std::cerr << "Error: bind, please try another port\n";
		close (server_socket_fd);
		return (1);
	}

	//	set server socket start to listen
	if (listen(server_socket_fd, 100) == -1)
	{
		std::cerr << "Error: listen\n";
		close (server_socket_fd);
		return (1);
	}

	//	create epoll instance
	int	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
		std::cerr << "Error: epoll_create1\n";
		return (1);
	}

	epoll_event	interest;
	interest.events = EPOLLIN | EPOLLET;
	interest.data.fd = server_socket_fd;

	//	add, delete or modify events with epoll_ctl
	int	status = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket_fd, &interest);
	if (status == -1)
	{
		std::cerr << "Error: epoll_ctl, add, server fd\n";
		return (1);
	}

	Server	server(server_socket_fd, epoll_fd, SERVER_NAME, password, server_address);
	// std::cout << "Server start on port " << ntohs(server.getAddr().sin_port)
	// << "\nPassword(evaluation only): " << server.getPass() << "\n";
	std::cout << server;

	struct epoll_event	pending[MAX_READY_EVENTS];
	char		buff[BUFFER_SIZE + 1];
	std::string	input;

	while (1)
	{
		//	wait events for registered file descriptors
		int	event_n = epoll_wait(epoll_fd, pending, MAX_READY_EVENTS, -1);
		if (event_n == -1)
		{
			std::cerr << "Error: epoll_wait\n";
			return (1);
		}

		// loop through events which have input
		for (int i = 0; i < event_n; i++)
		{
			//	accept connection request for server socket and only accept
			//	no receieve or send in this part
			if (pending[i].data.fd == server_socket_fd)
			{
				sockaddr_in	socket_addr;
				socklen_t	socket_len = sizeof(socket_addr);

				// check if client limit reached
				if (server.getClients().size() == MAX_CLIENTS)
				{
					// send deny response if there is,
					// or just ignore
					continue ;
				}

				// accept connection
				int client_fd = accept(server_socket_fd, (sockaddr *) &socket_addr, &socket_len);
				if (client_fd == -1)
				{
					if (errno != EAGAIN && errno != EWOULDBLOCK)
					{
						std::cerr << errno << "Error: accept\n";
						continue ;
					}
				}

				//set fd as non-blocking
				fcntl(client_fd, F_SETFL, O_NONBLOCK);

				// set event for client to add interest list
				epoll_event	client_event;
				client_event.events = EPOLLIN | EPOLLET;
				client_event.data.fd = client_fd;

				//	add client to interest list. let epoll listen to client
				if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event) == -1)
				{
					std::cerr << "Error epoll_ctl, client\n";
					continue ;
				}

				Client	*client = new Client(client_fd);
				client->setConnected(0); // can be set as default
				server.addClient(client);
			}
			else if (pending[i].events & EPOLLIN)
			{
				//	Read incoming messages:
				//	Read all data for event because it is edge triggered epoll.
				//	It only triggers per message.
				//	If you dont get the whole message here, you will wait until next message
				int	len = BUFFER_SIZE;
				while (len == BUFFER_SIZE)
				{
					len = recv(pending[i].data.fd, buff, BUFFER_SIZE, 0);
					if (len == 0 || (len == -1 && errno != EAGAIN && errno != EWOULDBLOCK))
					{
						std::cout << "Disconnected fd: " << pending[i].data.fd << "\n";
						//	closing fd automaticly remove fd from interest list. using epoll_ctl wit DEL option is for clarity
						epoll_ctl(epoll_fd, EPOLL_CTL_DEL, pending[i].data.fd, NULL);
						server.removeClient(server.findClientByFd(pending[i].data.fd));
						// removeClient also close fd
						// close(pending[i].data.fd);
						continue ;
					}
					if (len == -1)
						continue ;
					buff[len] = '\0';
					input.append(buff, len);
				}
				// HANDLE EVENTS HERE
				// data.fd is client's socket file descripter
				server.handleRequest(input, pending[i].data.fd);
				input = "";
			}
			else
			{
				std::cout << "Disconnected ANOTHER EVENT: " << pending[i].data.fd << "\n";
				//	closing fd automaticly remove fd from interest list. using epoll_ctl wit DEL option is for clarity
				epoll_ctl(epoll_fd, EPOLL_CTL_DEL, pending[i].data.fd, NULL);
				server.removeClient(server.findClientByFd(pending[i].data.fd));
				// removeClient also close fd
				// close(pending[i].data.fd);
			}
		}
	}
	return (0);
}
