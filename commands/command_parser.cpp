#include "Command.hpp"
#include "CommandExceptions.hpp"
#include "KickCommand.hpp"
#include "InviteCommand.hpp"
#include "TopicCommand.hpp"
#include "ModeCommand.hpp"
#include "CapCommand.hpp"
#include "JoinCommand.hpp"
#include "PrivmsgCommand.hpp"
#include "PingCommand.hpp"
#include "PartCommand.hpp"
#include "QuitCommand.hpp"
#include "NickCommand.hpp"
#include "PassCommand.hpp"
#include "UserCommand.hpp"
#include "WhoCommand.hpp"
#include "WhoisCommand.hpp"
#include "LusersCommand.hpp"
#include "ListCommand.hpp"
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <vector>

static char toUpperChar(char c)
{
    return std::toupper(static_cast<unsigned char>(c));
}

Command *parseCommand(const std::string &input)
{
    std::istringstream iss(input.c_str());
    std::string cmdType;
    std::string token;
    std::vector<std::string> params;

    if (!(iss >> cmdType))
    {
        throw UnknownCommandException("");
    }

    std::transform(cmdType.begin(), cmdType.end(), cmdType.begin(), toUpperChar);

    while (iss >> token)
    {
        // Handle parameters that start with ':' (trailing parameter)
        if (token[0] == ':')
        {
            std::string trailing = token.substr(1);
            std::string remainder;
            if (std::getline(iss, remainder))
            {
                trailing += remainder;
            }
            if (trailing[trailing.length() - 1] == '\r')
                trailing.erase(trailing.end() - 1);
            params.push_back(trailing);
            break;
        }
        params.push_back(token);
    }

    // Create appropriate command object with validation
    if (cmdType == "KICK")
    {
        // KICK <channel> <user> [<reason>]
        if (params.size() < 2)
        {
            throw MissingParametersException("KICK", "Not enough parameters");
        }
        std::string reason = params.size() > 2 ? params[2] : "";
        return new KickCommand(params[0], params[1], reason);
    }
    else if (cmdType == "INVITE")
    {
        // INVITE <nickname> <channel>
        if (params.size() != 2)
        {
            throw MissingParametersException("INVITE", "Not enough parameters");
        }
        return new InviteCommand(params[0], params[1]);
    }
    else if (cmdType == "TOPIC")
    {
        // TOPIC <channel> [<topic>]
        if (params.size() < 1)
        {
            throw MissingParametersException("TOPIC", "Not enough parameters");
        }
        std::string topic = params.size() > 1 ? params[1] : "";
        return new TopicCommand(params[0], topic);
    }
    else if (cmdType == "MODE")
    {
        // MODE <target> [<modestring> [<mode params>...]]
        if (params.size() < 1)
        {
            throw MissingParametersException("MODE", "Not enough parameters");
        }

        std::string target = params[0];
        std::string modeString = params.size() > 1 ? params[1] : "";

        std::string modeParams = "";
        for (size_t i = 2; i < params.size(); i++)
        {
            if (i > 2)
                modeParams += " ";
            modeParams += params[i];
        }

        return new ModeCommand(target, modeString, modeParams);
    }
    else if (cmdType == "CAP")
    {
        // CAP <subcommand> [<capabilities>]
        if (params.size() < 1)
        {
            throw MissingParametersException("CAP", "Not enough parameters");
        }
        std::string capabilities = params.size() > 1 ? params[1] : "";
        return new CapCommand(params[0], capabilities);
    }
    else if (cmdType == "JOIN")
    {
        // JOIN <channel>{,<channel>} [<key>{,<key>}]
        if (params.size() < 1)
        {
            throw MissingParametersException("JOIN", "Not enough parameters");
        }

        std::vector<std::string> channels;
        std::istringstream channelStream(params[0]);
        std::string channel;
        while (std::getline(channelStream, channel, ','))
        {
            if (!channel.empty())
            {
                channels.push_back(channel);
            }
        }

        std::vector<std::string> keys;
        if (params.size() > 1)
        {
            std::istringstream keyStream(params[1]);
            std::string key;
            while (std::getline(keyStream, key, ','))
            {
                keys.push_back(key); // Empty keys are allowed
            }
        }

        return new JoinCommand(channels, keys);
    }
    else if (cmdType == "PRIVMSG")
    {
        // PRIVMSG <target> <message>
        if (params.size() < 2)
        {
            throw MissingParametersException("PRIVMSG", "Not enough parameters");
        }
        return new PrivmsgCommand(params[0], params[1]);
    }
    else if (cmdType == "PING")
    {
        // PING <server>
        if (params.size() < 1)
        {
            throw MissingParametersException("PING", "Not enough parameters");
        }
        return new PingCommand(params[0]);
    }
    else if (cmdType == "PART")
    {
        // PART <channel>{,<channel>} [<reason>]
        if (params.size() < 1)
        {
            throw MissingParametersException("PART", "Not enough parameters");
        }

        std::vector<std::string> channels;
        std::istringstream channelStream(params[0]);
        std::string channel;
        while (std::getline(channelStream, channel, ','))
        {
            if (!channel.empty())
            {
                channels.push_back(channel);
            }
        }

        std::string reason = params.size() > 1 ? params[1] : "";
        return new PartCommand(channels, reason);
    }
    else if (cmdType == "QUIT")
    {
        // QUIT [<message>]
        std::string message = params.size() > 0 ? params[0] : "";
        return new QuitCommand(message);
    }
    else if (cmdType == "NICK")
    {
        // NICK <nickname>
        if (params.size() < 1)
        {
            throw MissingParametersException("NICK", "Not enough parameters");
        }
        return new NickCommand(params[0]);
    }
    else if (cmdType == "PASS")
    {
        // PASS <password>
        if (params.size() < 1)
        {
            throw MissingParametersException("PASS", "Not enough parameters");
        }
        return new PassCommand(params[0]);
    }
    else if (cmdType == "USER")
    {
        // USER <username> <hostname> <servername> <realname>
        if (params.size() < 4)
        {
            throw MissingParametersException("USER", "Not enough parameters");
        }

        return new UserCommand(params[0], params[1], params[2], params[3]);
    }
    else if (cmdType == "WHO")
    {
        // WHO <mask>
        if (params.size() < 1)
        {
            throw MissingParametersException("WHO", "Not enough parameters");
        }
        std::string mask = params[0];
        return new WhoCommand(mask);
    }
    else if (cmdType == "WHOIS")
    {
        // WHOIS [<target>] <nickname>
        if (params.size() < 1)
        {
            throw MissingParametersException("WHOIS", "Not enough parameters");
        }
        if (params.size() >= 2)
        {
            return new WhoisCommand(params[0], params[1]);
        }
        else
        {
            return new WhoisCommand(params[0]);
        }
    }
    else if (cmdType == "LUSERS")
    {
        // LUSERS
        return new LusersCommand();
    }
    else if (cmdType == "LIST")
    {
        // LIST [<channel>{,<channel>}]
        std::vector<std::string> channels;
        if (params.size() > 0)
        {
            std::istringstream channelStream(params[0]);
            std::string channel;
            while (std::getline(channelStream, channel, ','))
            {
                if (!channel.empty())
                {
                    channels.push_back(channel);
                }
            }
        }
        return new ListCommand(channels);
    }
    else
    {
        throw UnknownCommandException(cmdType);
    }
}
