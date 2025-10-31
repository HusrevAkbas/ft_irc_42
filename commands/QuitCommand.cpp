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

    // response.append(":").append(server.getName())
    // .append(" QUIT :").append(this->message).append("\r\n");
    // server.sendResponse(client, response);
    server.removeClient(&client);
}
