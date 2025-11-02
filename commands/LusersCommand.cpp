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
	std::stringstream	ss;

	ss << server.getClients().size();
	std::string	msg = "There are ";
	msg += ss.str();
	msg += " users and 0 invisible on 0 servers";
	std::string	response = buildNumericReply(server, client, RPL_LUSERCLIENT, msg);
	server.sendResponse(client, response);

	msg = "I have ";
	msg += ss.str();
	msg += " clients and 0 servers";
	response = buildNumericReply(server, client, RPL_LUSERME, msg);
	server.sendResponse(client, response);

	ss.str("");
	ss << server.getChannels().size();
	response = ":" + server.getName() + " " + toString(RPL_LUSERCHANNELS) + " " + client.getNickname() + " ";
	response += ss.str();
	response += " :channels formed\r\n";
	server.sendResponse(client, response);

}
