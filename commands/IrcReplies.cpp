#include "IrcReplies.hpp"
#include <sstream>


std::string toString(IrcReply code) {
    std::ostringstream oss;
    oss << static_cast<int>(code);
    return oss.str();
}
