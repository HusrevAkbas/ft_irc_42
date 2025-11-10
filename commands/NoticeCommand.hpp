#pragma once

#include "Command.hpp"
#include <string>

class NoticeCommand : public Command {
private:
    std::string target;
    std::string message;

public:
    NoticeCommand();
    NoticeCommand(const std::string& target, const std::string& message);
    NoticeCommand(const NoticeCommand& other);
    NoticeCommand& operator=(const NoticeCommand& other);
    ~NoticeCommand();

    std::string getMessage() const;
    std::string getTarget() const;
    void response(Client &client, Server &server);
};
