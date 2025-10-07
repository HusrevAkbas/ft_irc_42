#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

class Command {
protected:
    std::string type;

public:
    Command(const std::string& cmdType);
    virtual ~Command();

    std::string getType() const;
};

#endif
