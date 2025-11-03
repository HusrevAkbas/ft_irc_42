#include "UserCommand.hpp"

UserCommand::UserCommand() : Command("USER") {}

UserCommand::UserCommand(const std::string &user, const std::string &host, const std::string &server, const std::string &real)
    : Command("USER"), username(user), hostname(host), servername(server), realname(real) {}

UserCommand::UserCommand(const UserCommand &other) : Command("USER")
{
    *this = other;
}

UserCommand &UserCommand::operator=(const UserCommand &other)
{
    if (this != &other)
    {
        Command::operator=(other);
        username = other.username;
        hostname = other.hostname;
        servername = other.servername;
        realname = other.realname;
    }
    return *this;
}

UserCommand::~UserCommand() {}

std::string UserCommand::getUsername() const
{
    return username;
}

std::string UserCommand::getHostname() const
{
    return hostname;
}

std::string UserCommand::getServername() const
{
    return servername;
}

std::string UserCommand::getRealname() const
{
    return realname;
}

void UserCommand::response(Client &client, Server &server)
{
    std::string response;

    if (client.getConnected())
    {
        response = Command::buildNumericReply(server, client, ERR_ALREADYREGISTERED, "You are already registered");
        server.sendResponse(client, response);
        return ;
    }
    client.setUsername(this->username);
    client.setHostname(this->hostname);
    client.setNetworkname(this->servername);
    client.setRealname(this->realname);
}
