#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "Command.hpp"
#include <string>

class NickCommand : public Command {
private:
    std::string nickname;

public:
    NickCommand(const std::string& nick);
    virtual ~NickCommand();

    std::string getNickname() const;

    void response(Client &client, Server &server);
};

#endif
