#pragma once

#include "Command.hpp"

class LusersCommand : public Command
{
	public:
		LusersCommand();
		LusersCommand(const LusersCommand& other);
		LusersCommand& operator=(const LusersCommand& other);
		~LusersCommand();

		void response(Client &client, Server &server);
};
