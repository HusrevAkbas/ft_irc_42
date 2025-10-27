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

    if (client.getConnected())
    {
        response = Command::buildNumericReply(server, client, ERR_ALREADYREGISTERED, "You are already registered");
    }
    else if (this->password.empty())
    {
        response = Command::buildNumericReply(server, client, ERR_NEEDMOREPARAMS, "You must provide password");
        server.sendResponse(client, response);
    }
    else
    {
        // TODO set client password, check password match on CAP END
        if (server.getPass() != this->password)
        {
            response = Command::buildNumericReply(server, client, ERR_PASSWDMISMATCH, "Wrong password mate");
            server.sendResponse(client, response);
        }
    }
}
