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
	(void)client;
	(void)server;
}
