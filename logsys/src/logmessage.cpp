#include "logmessage.hpp"
#include "timestamp.hpp"
namespace tulun
{
    logmessage::logmessage(const tulun::LOG_LEVEL &level,
                           const std::string &filename,
                           const std::string &funcname,
                           const int line) : head_{}, test_{}, level_(level)
    {
        std::stringstream ss;
        ss << tulun::timestamp::Now().toformattedstring() << " ";
        ss << tulun::LLTOSTR[static_cast<int>(level_)] << " ";
        auto pos = filename.find_last_of('/');
        std::string fname = filename.substr(pos + 1);
        ss << fname << " " << funcname << " " << line << " ";
        head_ = ss.str();
    }
    logmessage::~logmessage()
    {
    }
    tulun::LOG_LEVEL logmessage::getlevel() const
    {
        return level_;
    }
    const std::string logmessage::tostring() const
    {
        return head_ + test_;
    }
};
