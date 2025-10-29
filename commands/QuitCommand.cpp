#include "QuitCommand.hpp"

QuitCommand::QuitCommand() : Command("QUIT") {}

QuitCommand::QuitCommand(const std::string& msg)
    : Command("QUIT"), message(msg) {}

QuitCommand::QuitCommand(const QuitCommand& other) : Command("QUIT") {
    *this = other;
}

QuitCommand& QuitCommand::operator=(const QuitCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        message = other.message;
    }
    return *this;
}

QuitCommand::~QuitCommand() {}

std::string QuitCommand::getMessage() const {
    return message;
}

void QuitCommand::response(Client &client, Server &server)
{
    std::string response;

    response += ":" + client.getNickname() + " QUIT :Quit: ";
    if (this->message.empty())
        response += "\r\n";
    else
        response += this->message + "\n";

    for (size_t i = 0; i < client.getChannels().size(); i++)
    {
        client.getChannels()[i]->broadcast(client, server, response);
    }

    server.removeClient(&client);
}
