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