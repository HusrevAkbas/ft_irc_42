#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include "Command.hpp"
#include <string>

class ModeCommand : public Command {
private:
    std::string channel;
    std::string mode;
    std::string modeParams;

public:
    ModeCommand(const std::string& chan, const std::string& mod, const std::string& params);
    virtual ~ModeCommand();

    std::string getChannel() const;
    std::string getMode() const;
    std::string getModeParams() const;
};

#endif
