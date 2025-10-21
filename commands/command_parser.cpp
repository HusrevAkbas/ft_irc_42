#include "Command.hpp"
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
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <vector>

static char toUpperChar(char c) {
    return std::toupper(static_cast<unsigned char>(c));
}

Command* parseCommand(const std::string& input) {
    std::istringstream iss(input.c_str());
    std::string cmdType;
    std::string token;
    std::vector<std::string> params;

    // Extract command type
    if (!(iss >> cmdType)) {
        throw std::invalid_argument("Invalid command: empty input");
    }

    // Convert to uppercase for case-insensitive comparison
    std::transform(cmdType.begin(), cmdType.end(), cmdType.begin(), toUpperChar);

    // Extract parameters
    while (iss >> token) {
        // Handle parameters that start with ':' (trailing parameter)
        if (token[0] == ':') {
            std::string trailing = token.substr(1);
            std::string remainder;
            if (std::getline(iss, remainder)) {
                trailing += remainder;
            }
            params.push_back(trailing);
            break;
        }
        params.push_back(token);
    }

    // Create appropriate command object with validation
    if (cmdType == "KICK") {
        // KICK <channel> <user> [<reason>]
        if (params.size() < 2) {
            throw std::invalid_argument("KICK command requires at least 2 parameters: <channel> <user>");
        }
        std::string reason = params.size() > 2 ? params[2] : "";
        return new KickCommand(params[0], params[1], reason);
    } else if (cmdType == "INVITE") {
        // INVITE <nickname> <channel>
        if (params.size() != 2) {
            throw std::invalid_argument("INVITE command requires 2 parameters: <nickname> <channel>");
        }
        return new InviteCommand(params[0], params[1]);
    } else if (cmdType == "TOPIC") {
        // TOPIC <channel> [<topic>]
        if (params.size() < 1) {
            throw std::invalid_argument("TOPIC command requires at least 1 parameter: <channel>");
        }
        std::string topic = params.size() > 1 ? params[1] : "";
        return new TopicCommand(params[0], topic);
    } else if (cmdType == "MODE") {
        // MODE <channel> <mode> [<mode params>]
        if (params.size() < 2) {
            throw std::invalid_argument("MODE command requires at least 2 parameters: <channel> <mode>");
        }
        std::string modeParams = params.size() > 2 ? params[2] : "";
        return new ModeCommand(params[0], params[1], modeParams);
    } else if (cmdType == "CAP") {
        // CAP <subcommand> [<capabilities>]
        if (params.size() < 1) {
            throw std::invalid_argument("CAP command requires at least 1 parameter: <subcommand>");
        }
        std::string capabilities = params.size() > 1 ? params[1] : "";
        return new CapCommand(params[0], capabilities);
    } else if (cmdType == "JOIN") {
        // JOIN <channel> [<key>]
        if (params.size() < 1) {
            throw std::invalid_argument("JOIN command requires at least 1 parameter: <channel>");
        }
        std::string key = params.size() > 1 ? params[1] : "";
        return new JoinCommand(params[0], key);
    } else if (cmdType == "PRIVMSG") {
        // PRIVMSG <target> <message>
        if (params.size() < 2) {
            throw std::invalid_argument("PRIVMSG command requires 2 parameters: <target> <message>");
        }
        return new PrivmsgCommand(params[0], params[1]);
    } else if (cmdType == "PING") {
        // PING <server>
        if (params.size() < 1) {
            throw std::invalid_argument("PING command requires 1 parameter: <server>");
        }
        return new PingCommand(params[0]);
    } else if (cmdType == "PART") {
        // PART <channel> [<reason>]
        if (params.size() < 1) {
            throw std::invalid_argument("PART command requires at least 1 parameter: <channel>");
        }
        std::string reason = params.size() > 1 ? params[1] : "";
        return new PartCommand(params[0], reason);
    } else if (cmdType == "QUIT") {
        // QUIT [<message>]
        std::string message = params.size() > 0 ? params[0] : "";
        return new QuitCommand(message);
    } else if (cmdType == "NICK") {
        // NICK <nickname>
        if (params.size() < 1) {
            throw std::invalid_argument("NICK command requires 1 parameter: <nickname>");
        }
        return new NickCommand(params[0]);
    } else if (cmdType == "PASS") {
        // PASS <password>
        if (params.size() < 1) {
            throw std::invalid_argument("PASS command requires 1 parameter: <password>");
        }
        return new PassCommand(params[0]);
    } else if (cmdType == "USER") {
        // USER <username> <hostname> <servername> <realname>
        if (params.size() < 4) {
            throw std::invalid_argument("USER command requires 4 parameters: <username> 0 * <realname>");
        }
        if (params[1] != "0" || params[2] != "*") {
            throw std::invalid_argument("USER command parameters 2 and 3 should be '0' and '*'");
        }
        return new UserCommand(params[0], params[3]);
    } else {
        throw std::invalid_argument("Invalid command: " + cmdType);
    }
}
