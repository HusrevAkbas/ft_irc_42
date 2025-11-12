#include "CapCommand.hpp"
#include "CapMOTD.hpp"

CapCommand::CapCommand() : Command("CAP") {}

CapCommand::CapCommand(const std::string& subcmd, const std::string& caps)
    : Command("CAP"), subcommand(subcmd), capabilities(caps) {}

CapCommand::CapCommand(const CapCommand& other) : Command("CAP") {
    *this = other;
}

CapCommand& CapCommand::operator=(const CapCommand& other) {
    if (this != &other) {
        Command::operator=(other);
        subcommand = other.subcommand;
        capabilities = other.capabilities;
    }
    return *this;
}

CapCommand::~CapCommand() {}

std::string CapCommand::getSubcommand() const {
    return subcommand;
}

std::string CapCommand::getCapabilities() const {
    return capabilities;
}

void    CapCommand::response(Client &client, Server &server)
{
    std::string response;
    std::string message;

    if (this->subcommand == "LS")
    {
        response.append(":")
            .append(server.getName())
            .append(" CAP * LS\r\n");
        server.sendResponse(client, response);
    }
    if (this->subcommand == "END")
    {
        if (server.getPass() != client.getPassword())
        {
            server.removeClient(&client);
            return ;
        }
        if (client.getNickname().empty())
        {
            server.removeClient(&client);
            return ;
        }
        Client  *found = server.findClientByNick(client.getNickname());
        if (found != &client)
        {
            response = "ERROR :Nickname is already in use\r\n";
            server.sendResponse(client, response);
            server.removeClient(&client);
            return ; // throw std::invalid_argument("Nickname is in use");
        }
        client.setConnected(1);
        //  send greet messages
        //  001 welcome
        message = "Welcome to 42 network, ";
        message += client.getNickname();
        response = Command::buildNumericReply(server, client, RPL_WELCOME, message);
        server.sendResponse(client, response);
        //  002 yourhost
        message = "Your host is ";
        message.append(server.getName()).append(", version 1.2.3");
        response = Command::buildNumericReply(server,client, RPL_YOURHOST, message);
        server.sendResponse(client, response);
        //  003 created
        time_t  serverTime = server.getTimestamp();
        message = "This server was created ";
        message += std::ctime(&serverTime);
        response = Command::buildNumericReply(server,client, RPL_CREATED, message);
        server.sendResponse(client, response);
        //  004 myinfo
        message = "";
        message.append(server.getName()).append(" v-1.2.3");
        response = Command::buildNumericReplyNoColon(server,client, RPL_MYINFO, message, "");
        server.sendResponse(client, response);
        //  005 isupport
        message = "CASEMAPPING=ascii CHANLIMIT=#:25 CHANMODES=,o,kl,it PREFIX=(ov)@+";
        message += " CHANTYPES=# NETWORK=42 STATUSMSG=@+ SAFELIST";
        response = Command::buildNumericReply(server, client, RPL_ISUPPORT, message, "are supported by this server");
        server.sendResponse(client, response);
        // a response as if client send LUSER
        server.handleRequest("LUSERS", client.getSocketFd());
        // MOTD message of the day
        message = "--- Message of the day from " + server.getName() + " ---";
        response = buildNumericReply(server, client, RPL_MOTDSTART, message);
        server.sendResponse(client, response);
        std::stringstream   ss(motd);
        while (std::getline(ss, message))
        {
            response = buildNumericReply(server, client, RPL_MOTD, message);
            server.sendResponse(client, response);
        }
        message = "End of /MOTD";
        response = Command::buildNumericReply(server, client, RPL_ENDOFMOTD, message);
        server.sendResponse(client, response);
    }
}
