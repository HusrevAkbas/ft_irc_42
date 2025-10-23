#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "Command.hpp"
#include <string>

class PassCommand : public Command {
private:
    std::string password;

public:
    PassCommand(const std::string& pass);
    virtual ~PassCommand();

    std::string getPassword() const;

    void response(Client &client, Server &server);
};

#endif
