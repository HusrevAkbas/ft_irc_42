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
	(void)server;
	(void)client;
}
