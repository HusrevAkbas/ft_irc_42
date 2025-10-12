#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "Command.hpp"
#include <string>

class UserCommand : public Command {
private:
    std::string username;
    std::string realname;

public:
    UserCommand(const std::string& user, const std::string& real);
    virtual ~UserCommand();

    std::string getUsername() const;
    std::string getRealname() const;
};

#endif
