#include "PassCommand.hpp"

PassCommand::PassCommand() : Command("PASS") {}

PassCommand::PassCommand(const std::string& pass)
    : Command("PASS"), password(pass) {}

PassCommand::PassCommand(const PassCommand& other) : Command("PASS") {
    *this = other;
}

PassCommand& PassCommand::operator=(const PassCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        password = other.password;
    }
    return *this;
}

PassCommand::~PassCommand() {}

std::string PassCommand::getPassword() const {
    return password;
}

void PassCommand::response(Client &client, Server &server)
{
    std::string response;

    if (client.getRegistered())
    {
        response = Command::buildNumericReply(server, client, ERR_ALREADYREGISTERED, "You are already registered");
        server.sendResponse(client, response);
    }
    else if (this->password.empty())
    {
        response = Command::buildNumericReply(server, client, ERR_NEEDMOREPARAMS, "You must provide password");
        server.sendResponse(client, response);
    }
    else
    {
        if (server.getPass() != this->password)
		{
            response = buildNumericReply(server, client, ERR_PASSWDMISMATCH, "Wrong password mate!");
            server.sendResponse(client, response);
            server.removeClient(&client);
            return ;
		} else {
            client.setPassword(this->password);
        }
    }
}
