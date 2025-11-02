#pragma once

#include "Command.hpp"

class WhoCommand : public Command
{
	private:
		std::string mask;

	public:
		WhoCommand();
		WhoCommand(const std::string& maskParam);
		WhoCommand(const WhoCommand& other);
		WhoCommand& operator=(const WhoCommand& other);
		~WhoCommand();

		std::string getMask() const;
		void response(Client &client, Server &server);
};
