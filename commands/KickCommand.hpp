#pragma once

#include "Command.hpp"
// #include "Server.hpp"
// #include "Client.hpp"
#include <string>

class KickCommand : public Command {
private:
    std::string _channel;
    std::string _target;
    std::string _reason;

public:
    KickCommand();
    KickCommand(const std::string& channel, const std::string& target, const std::string& reason);
    KickCommand(const KickCommand &source);
    KickCommand&    operator=(const KickCommand &source);
    virtual ~KickCommand();

    std::string getChannel() const;
    std::string getTarget() const;
    std::string getReason() const;
    
    void    setChannel(const std::string& channel);
    void    setTarget(const std::string& target);
    void    setReason(const std::string& reason);
    
    Client* findClient(const std::string& client, Channel* channel);
    // Client* findOperator(const std::string& client, Channel* channel);
    void    checkReason();
    void    execute(Server& server, Client& client);
    void    response(Client &client, Server &server);
};
