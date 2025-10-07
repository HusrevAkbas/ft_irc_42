#include "Server.hpp"

#define	BUFFER_SIZE	1000

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

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
	server_address.sin_port = htons(8081);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//	bind server socket and address
	if (bind(server_socket_fd, (sockaddr *) &server_address, sizeof(server_address)))
	{
		std::cerr << "Error: bind " << errno << "\n";
		close (server_socket_fd);
		return (1);
	}

	//	set server socket ready to listen
	if (listen(server_socket_fd, 100) == -1)
	{
		std::cerr << "Error: listen " << errno << "\n";
		close (server_socket_fd);
		return (1);
	}

	//	create epoll instance
	int	efd = epoll_create1(0);
	if (efd == -1)
	{
		std::cerr << "Error: epoll_create1\n";
		return (1);
	}

	epoll_event	interest;
	interest.events = EPOLLIN | EPOLLET;
	interest.data.fd = server_socket_fd;

	//	add, delete or modify events with epoll_ctl
	int	status = epoll_ctl(efd, EPOLL_CTL_ADD, server_socket_fd, &interest);
	if (status == -1)
	{
		std::cerr << "Error: epoll_ctl, add, server fd\n";
		return (1);
	}

	struct epoll_event	pending[20];
	char		buff[BUFFER_SIZE];
	std::string	input;
	std::string	toSend = "this is from SERVER";

	while (1)
	{
		//	wait events for registered file descriptors
		int	event_n = epoll_wait(efd, pending, 20, -1);
		if (event_n == -1)
		{
			std::cerr << "Error: epoll_wait\n";
			return (1);
		}
		for (int i = 0; i < event_n; i++)
		{
			//	accept connection request for server socket and only accept
			//	no receieve or send in this part
			if (pending[i].data.fd == server_socket_fd)
			{
				sockaddr_in	socket_addr;
				socklen_t	socket_len = sizeof(socket_addr);

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

				// set event for client to be able to add interest list
				epoll_event	client_event;
				client_event.events = EPOLLIN | EPOLLET;
				client_event.data.fd = client_fd;

				//	add client to interest list. let epoll listen to client
				if (epoll_ctl(efd, EPOLL_CTL_ADD, client_fd, &client_event) == -1)
				{
					std::cerr << "Error epoll_ctl, client\n";
					return (1);
				}
			}
			else if (pending[i].events & EPOLLIN)
			{
				//	read incoming messages in this part, read all data for event because
				//	it is edge triggered epoll. It only triggers per message.
				//	If you dont get the whole message, you will wait until next message
				int	len = 1;
				while (len > 0)
				{
					bzero(&buff, 1000);
					len = recv(pending[i].data.fd, buff, BUFFER_SIZE, 0);
					if (len == 0 || (len == -1 && errno != EAGAIN && errno != EWOULDBLOCK))
					{
						std::cout << "Disconnected BUFFER LEN = 0: fd: " << pending[i].data.fd << "\n";
						//	closing fd automaticly remove fd from interest list. using epoll_ctl wit DEL option is for clarity
						epoll_ctl(efd, EPOLL_CTL_DEL, pending[i].data.fd, NULL);
						close (pending[i].data.fd);
					}
					buff[len] = '\0';
					input += buff;
				}
				std::cout << input << "\n";
				// HANDLE EVENTS HERE
				input.clear();
			}
			else
			{
				std::cout << "Disconnected ANOTHER EVENT: " << pending[i].data.fd << "\n";
				//	closing fd automaticly remove fd from interest list. using epoll_ctl wit DEL option is for clarity
				epoll_ctl(efd, EPOLL_CTL_DEL, pending[i].data.fd, NULL);
				close(pending[i].data.fd);
			}
		}
	}
	return (0);
}
