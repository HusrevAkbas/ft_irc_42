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
		LEAVE
		QUIT
		NICK
		PASS
		USER

		WHO

ISSUES:
	23.10.2025:

	1- We should send response messages in case of missing arguments
	current: we throw an exception in case of wrong number of arguments
	expected: throw exception only if command is invalid, not supported

	2- USER command send 4 information depends on RFC standards
		<username> <hostname> <servername> <realname>
	OR	<username> <mode> <unused> <realname>.
	we should parse all parts
	current: Hüsrev commended out the part checks for second and third parameter
	expected: we should have 4 attributes in our Client class to store these infos