#pragma once

#include <string>

enum IrcReply {
    RPL_WELCOME         = 1,
    RPL_YOURHOST        = 2,
    RPL_CREATED         = 3,
    RPL_MYINFO          = 4,
    RPL_ISUPPORT        = 5,

    RPL_UMODEIS         = 221,

    RPL_CHANNELMODEIS   = 324,
    RPL_NOTOPIC         = 331,
    RPL_TOPIC           = 332,
    RPL_NAMREPLY        = 353,
    RPL_ENDOFNAMES      = 366,

    ERR_NOSUCHNICK          = 401,
    ERR_NOSUCHCHANNEL       = 403,
    ERR_TOOMANYCHANNELS     = 405,
    ERR_NOMOTD              = 422,
    ERR_NONICKNAMEGIVEN     = 431,
    ERR_NICKNAMEINUSE       = 433,
    ERR_NOTONCHANNEL        = 442,
    ERR_NEEDMOREPARAMS      = 461,
    ERR_ALREADYREGISTERED   = 462,
    ERR_PASSWDMISMATCH      = 464,
    ERR_CHANNELISFULL       = 471,
    ERR_UNKNOWNMODE         = 472,
    ERR_INVITEONLYCHAN      = 473,
    ERR_BADCHANNELKEY       = 475,
    ERR_CHANOPRIVSNEEDED    = 482
};

std::string toString(IrcReply code);
