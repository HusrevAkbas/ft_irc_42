#pragma once

#include <string>

enum IrcReply {
    RPL_WELCOME         = 1,
    RPL_YOURHOST        = 2,
    RPL_CREATED         = 3,
    RPL_MYINFO          = 4,
    RPL_ISUPPORT        = 5,

    RPL_UMODEIS         = 221,
    RPL_LUSERCLIENT     = 251,
    RPL_LUSERCHANNELS   = 254,
    RPL_LUSERME         = 255,

    RPL_WHOISUSER       = 311,
    RPL_WHOISSERVER     = 312,
    RPL_ENDOFWHO        = 315,
    RPL_ENDOFWHOIS      = 318,
    RPL_LISTSTART       = 321,
    RPL_LIST            = 322,
    RPL_LISTEND         = 323,
    RPL_CHANNELMODEIS   = 324,
    RPL_NOTOPIC         = 331,
    RPL_TOPIC           = 332,
    RPL_WHOREPLY        = 352,
    RPL_NAMREPLY        = 353,
    RPL_ENDOFNAMES      = 366,
    RPL_ENDOFBANS       = 368,

    ERR_NOSUCHNICK          = 401,
    ERR_NOSUCHCHANNEL       = 403,
    ERR_TOOMANYCHANNELS     = 405,
    ERR_UNKNOWNCOMMAND      = 421,
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
    ERR_CHANOPRIVSNEEDED    = 482,
    ERR_UMODEUNKNOWNFLAG    = 501,
    ERR_USERSDONTMATCH      = 502
};

std::string toString(IrcReply code);
