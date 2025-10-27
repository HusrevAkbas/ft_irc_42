TODO always check return value of recv ( <0: Error, ==0: Disconnect, >0: possibly not null terminated )
TODO close fds on exit or disconnection
TODO set client fd flag O_NONBLOCK
TODO set up a proper handshake to keep connection work
TODO delete client object when closing fd dedicated to client

Execution flow
1-	connection
2-	parse - manage
	2.1 - parse input 
	2.2 - parse output
3-	signal handling
4-	clean up

Classes
	Client
		fd
		username
		nick
		addr
		*Channels[]
	Server
		fd
		name
		pass
		addr
		*Clients[]
		*Channels[]
	Channel
		name	: #channelname MUST start with #
		Client	*operators[]
		string	pass
		bool	i_inviteonly
		string	topic
		bool	t_topicSetable
		bool	k_hasPass
		int		l_userLimit

		void	o_givePrivilege(&Client operator, &Client target)
		void	o_takePrivilege(&Client operator, &Client target)

	Commands
		KICK
		INVITE
		MODE
		TOPIC

		CAP
		JOIN
		PRIVMSG
		PING
		LEAVE -> PART
		QUIT
		NICK
		PASS
		USER

	new commands:
		WHO - client sends when he joins a channel
		WHOIS - not sure, saw it before but dont remember when we get this command

ISSUES:
	27.10.2025:

	1- We should send response messages in case of missing arguments
	current: we throw an exception in case of wrong number of arguments
	expected: throw exception only if command is invalid, not supported

	2- USER command send 4 information depends on RFC standards. irssi in campus computers sends: <username> <hostname> <servername> <realname>
	we should parse all parts and save in client class.
	current: Hüsrev commended out the part checks for second and third parameter in command parser
	expected: we should have 4 attributes for all 4 infos in our Client class to store. i skip this step for now. Can you add attributes to Client?
		username, hostname, servername, realname, password

	3- After joining a channel, if we send PART command, we have a crash. Logs are here:

		c3r9p6% ./ircserv 3333 SAFEME
		Server name: ircserv42
		Password: SAFEME
		Ip: 0.0.0.0
		Port: 3333
		Clients: 0
		Channels: 0
		Created at: Mon Oct 27 12:57:01 2025
		---REQUEST---: CAP LS
		---REQUEST---: PASS SAFEME
		---REQUEST---: NICK irssiUser
		---REQUEST---: USER huakbas huakbas 127.0.0.1 :Husrev Akbas
		---REQUEST---: CAP END
		---REQUEST---: MODE irssiUser +i
		---REQUEST---: PING ircserv42
		---REQUEST---: JOIN #cafe
		---REQUEST---: MODE #cafe
		---REQUEST---: WHO #cafe
		Exception catched in Server::handleRequest:
		std::exception
		---REQUEST---: PING ircserv42
		---REQUEST---: PART #cafe
		free(): double free detected in tcache 2
		zsh: IOT instruction (core dumped)  ./ircserv 3333 SAFEME

	4- As you see above, when we join a channel, client sends two more commands automatically. MODE #channel and WHO #channel. we also need to implement WHO

	5- client wants to change usermod with MODE user +i, but we handle only channel modes.