#include "Command.hpp"
#include "KickCommand.hpp"
#include "InviteCommand.hpp"
#include "TopicCommand.hpp"
#include "ModeCommand.hpp"
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
    } else {
        throw std::invalid_argument("Invalid command: " + cmdType);
    }
}
