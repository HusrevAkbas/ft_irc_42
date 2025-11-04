#include "WhoisCommand.hpp"
#include "../Server.hpp"
#include "../Channel.hpp"

WhoisCommand::WhoisCommand() : Command("WHOIS"), target(""), nickname("") {}

WhoisCommand::WhoisCommand(const std::string &nick)
	: Command("WHOIS"), target(""), nickname(nick) {}

WhoisCommand::WhoisCommand(const std::string &targetServer, const std::string &nick)
	: Command("WHOIS"), target(targetServer), nickname(nick) {}

WhoisCommand::WhoisCommand(const WhoisCommand &other)
	: Command(other), target(other.target), nickname(other.nickname) {}

WhoisCommand &WhoisCommand::operator=(const WhoisCommand &other)
{
	if (this != &other)
	{
		Command::operator=(other);
		this->target = other.target;
		this->nickname = other.nickname;
	}
	return *this;
}

WhoisCommand::~WhoisCommand() {}

std::string WhoisCommand::getTarget() const
{
	return this->target;
}

std::string WhoisCommand::getNickname() const
{
	return this->nickname;
}

void WhoisCommand::response(Client &client, Server &server)
{
	std::string response;
	
	if (this->nickname.empty())
	{
		// no nickname given
		response = buildNumericReply(server, client, ERR_NONICKNAMEGIVEN, "No nickname given");
		server.sendResponse(client, response);
		return ;
	}

	Client	*target = server.findClientByNick(this->nickname);

	if (!target)
	{
		// no suchnick
		response = ":" + server.getName() + " " + toString(ERR_NOSUCHNICK) + " " + client.getNickname()
		+ " " + this->nickname + " :No such nickname\r\n";
		server.sendResponse(client, response);
	}
	else
	{
		response = ":" + server.getName() + " " + toString(RPL_WHOISUSER) + " "
		+ client.getNickname() + " " + target->getNickname() + " " + target->getUsername()
		+ " " + target->getHostname() + " * :" + target->getRealname() + "\r\n";
		server.sendResponse(client, response);

		// response = ":" + server.getName() + " " + toString(RPL_WHOISSERVER) + " "
		// + client.getNickname() + " " + this->nickname + " " + server.getName();
		response = buildNumericReplyNoColon(server, client, RPL_WHOISSERVER, this->nickname, server.getName());
		server.sendResponse(client, response);

		response = ":" + server.getName() + " " + toString(RPL_ENDOFWHOIS) + " " + client.getNickname()
		+ " " + this->nickname + " :End of /WHOIS\r\n";
		server.sendResponse(client, response);
	}
}
