#include "LusersCommand.hpp"
#include "../Server.hpp"

LusersCommand::LusersCommand() : Command("LUSERS") {}

LusersCommand::LusersCommand(const LusersCommand &other)
	: Command(other) {}

LusersCommand &LusersCommand::operator=(const LusersCommand &other)
{
	if (this != &other)
	{
		Command::operator=(other);
	}
	return *this;
}

LusersCommand::~LusersCommand() {}

void LusersCommand::response(Client &client, Server &server)
{
	(void)client;
	(void)server;
	// TODO: implement
}
