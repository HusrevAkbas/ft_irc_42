#pragma once

#include <string>
#include "IrcReplies.hpp"

class Server;
class Client;

class Command {
protected:
    std::string type;

    static std::string buildNumericReply(Server &server, Client &client,
                                         IrcReply replyCode,
                                         const std::string& message);

    static std::string buildNumericReply(Server &server, Client &client,
                                         IrcReply replyCode,
                                         const std::string& target,
                                         const std::string& message);

    static std::string buildClientMessage(Client &client,
                                          const std::string& command,
                                          const std::string& params);

    static std::string buildNameReply(Server &server, Client &client,
                                      const std::string& channelName,
                                      const std::string& namesList);

    static std::string buildNumericReplyNoColon(Server &server, Client &client,
                                                 IrcReply replyCode,
                                                 const std::string& target,
                                                 const std::string& param);

public:
    Command();
    Command(const std::string& cmdType);
    Command(const Command& other);
    Command& operator=(const Command& other);
    virtual ~Command();

    std::string getType() const;
    virtual void response(Client &client, Server &server);
};


// included at bottom because otherwise recursive include generates an error
#include "../Server.hpp"
#include "../Client.hpp"