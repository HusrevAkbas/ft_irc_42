#include "Command.hpp"

Command::Command(const std::string& cmdType) : type(cmdType) {}

Command::~Command() {}

std::string Command::getType() const {
    return type;
}

/* 
    Every derived class handles in its own way to response
    TODO: this is default for all classes. After implementing all overload functions in derived classes, make this function pure and remove implementation from base class
*/
void    Command::response(Client &client, Server &server)
{
    std::cout << YELLOW << "Command: " << RESET << this->type << "\n";
}
