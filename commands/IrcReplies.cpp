#include "IrcReplies.hpp"
#include <sstream>
#include <iomanip>

std::string toString(IrcReply code) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(3) << static_cast<int>(code);
    return oss.str();
}
