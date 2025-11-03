#include "WhoCommand.hpp"
#include "../Server.hpp"
#include "../Channel.hpp"

WhoCommand::WhoCommand() : Command("WHO"), mask("") {}

WhoCommand::WhoCommand(const std::string &maskParam)
	: Command("WHO"), mask(maskParam) {}

WhoCommand::WhoCommand(const WhoCommand &other)
	: Command(other), mask(other.mask) {}

WhoCommand &WhoCommand::operator=(const WhoCommand &other)
{
	if (this != &other)
	{
		Command::operator=(other);
		this->mask = other.mask;
	}
	return *this;
}

WhoCommand::~WhoCommand() {}

std::string WhoCommand::getMask() const
{
	return this->mask;
}

void WhoCommand::response(Client &client, Server &server)
{
	std::string response;
	std::vector<Client *> matchingClients;

	if (this->mask[0] == '#')
	{
		Channel *channel = server.findChannelByName(this->mask);
		if (channel)
		{
			matchingClients = channel->getClients();
		}
	}
	else
	{
		Client *targetClient = server.findClientByNick(this->mask);
		if (targetClient)
		{
			matchingClients.push_back(targetClient);
		}
	}

	for (size_t i = 0; i < matchingClients.size(); i++)
	{
		Client *targetClient = matchingClients[i];

		std::string channelName = "*";
		std::string userStatus = "";

		if (!this->mask.empty() && this->mask[0] == '#')
		{
			channelName = this->mask;
			Channel *channel = server.findChannelByName(this->mask);
			if (channel && channel->isOperator(*targetClient))
			{
				userStatus = "@";
			}
		}

		std::string flags = "H" + userStatus;

		response += ":" + server.getName() + " 352 " + client.getNickname() + " ";
		response += channelName + " ";
		response += targetClient->getUsername() + " ";
		response += targetClient->getHostname() + " ";
		response += server.getName() + " ";
		response += targetClient->getNickname() + " ";
		response += flags + " :0 ";
		response += targetClient->getRealname() + "\r\n";
	}

	response += buildNumericReply(server, client, RPL_ENDOFWHO, this->mask, "End of WHO list");

	server.sendResponse(client, response);
}
