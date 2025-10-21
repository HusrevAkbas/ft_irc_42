#ifndef QUITCOMMAND_HPP
#define QUITCOMMAND_HPP

#include "Command.hpp"
#include <string>

class QuitCommand : public Command {
private:
    std::string message;

public:
    QuitCommand(const std::string& msg = "");
    virtual ~QuitCommand();

    std::string getMessage() const;
};

#endif
