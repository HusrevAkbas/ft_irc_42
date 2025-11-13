#include "ListCommand.hpp"
#include "../Server.hpp"
#include "../Channel.hpp"

ListCommand::ListCommand() : Command("LIST") {}

ListCommand::ListCommand(const std::vector<std::string>& channelList)
	: Command("LIST"), channels(channelList) {}

ListCommand::ListCommand(const ListCommand& other)
	: Command(other), channels(other.channels) {}

ListCommand& ListCommand::operator=(const ListCommand& other)
{
	if (this != &other)
	{
		Command::operator=(other);
		this->channels = other.channels;
	}
	return *this;
}

ListCommand::~ListCommand() {}

std::vector<std::string> ListCommand::getChannels() const
{
	return this->channels;
}

void ListCommand::response(Client &client, Server &server)
{
	std::string	response;
	std::stringstream	ss;

	if (this->channels.size() == 0)
	{
		// list start
		response = ":" + server.getName() + " " + toString(RPL_LISTSTART)
		+ client.getNickname() + " Channel :Channel Users Topic\r\n";
		server.sendResponse(client, response);
		// list
		for (size_t i = 0; i < server.getChannels().size(); i++)
		{
			ss.str("");
			ss << server.getChannels()[i]->getClients().size();
			response = ":" + server.getName() + " " + toString(RPL_LIST) + " "
			+ client.getNickname() + " " + server.getChannels()[i]->getName() + " "
			+ ss.str() + " :" + server.getChannels()[i]->getTopic() + "\r\n";
			server.sendResponse(client, response);
		}
		// end of list
		response = buildNumericReply(server, client, RPL_LISTEND, "End of /LIST");
		server.sendResponse(client, response);
		return ;
	}
	// else check if channel exist 
	for (size_t i = 0; i < this->channels.size(); i++)
	{
		if (this->channels[i][0] != '#')
			this->channels[i].insert(this->channels[i].begin(), '#');
		Channel	*chan = server.findChannelByName(this->channels[i]);
		if (chan)
		{
			ss.str("");
			ss << chan->getClients().size();
			response = ":" + server.getName() + " " + toString(RPL_LIST) + " " + client.getNickname()
			+ " " + chan->getName() + " " + ss.str() + " :" + chan->getTopic() + "\r\n";
		}
		else
			response = buildNumericReplyNoColon(server, client, ERR_NOSUCHCHANNEL, this->channels[i], "");
		server.sendResponse(client, response);
	}
	response = buildNumericReply(server, client, RPL_LISTEND, "End of /LIST");
	server.sendResponse(client, response);
}
