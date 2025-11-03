#pragma once

#include "Command.hpp"
#include <vector>

class ListCommand : public Command
{
	private:
		std::vector<std::string> channels;

	public:
		ListCommand();
		ListCommand(const std::vector<std::string>& channelList);
		ListCommand(const ListCommand& other);
		ListCommand& operator=(const ListCommand& other);
		~ListCommand();

		std::vector<std::string> getChannels() const;
		void response(Client &client, Server &server);
};
