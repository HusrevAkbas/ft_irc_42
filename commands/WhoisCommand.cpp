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
	(void)client;
	(void)server;
}
