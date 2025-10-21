#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <iostream> // used only for std::cout in response, can be removed as soon as response is pure

#include "../Client.hpp"
class Server;

class Command {
protected:
    std::string type;

public:
    Command(const std::string& cmdType);
    virtual ~Command();

    std::string getType() const;
    virtual void response(Client &client, Server &server);
};

// included at bottom because otherwise recursive include generates an error
#include "../Server.hpp"

#endif
