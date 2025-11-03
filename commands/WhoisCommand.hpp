#pragma once

#include "Command.hpp"

class WhoisCommand : public Command
{
	private:
		std::string target;
		std::string nickname;

	public:
		WhoisCommand();
		WhoisCommand(const std::string& nick);
		WhoisCommand(const std::string& targetServer, const std::string& nick);
		WhoisCommand(const WhoisCommand& other);
		WhoisCommand& operator=(const WhoisCommand& other);
		~WhoisCommand();

		std::string getTarget() const;
		std::string getNickname() const;
		void response(Client &client, Server &server);
};
