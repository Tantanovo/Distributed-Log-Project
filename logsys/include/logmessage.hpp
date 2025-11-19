
#ifndef logmessage_hpp
#define logmessage_hpp
//c++ stl
#include<string>
using namespace std;
//owner
#include"logcommon.hpp"

namespace tulun{
    class logmessage{
        std::string head_;
        std::string test_;
        tulun::LOG_LEVEL level_;
    public:
        logmessage(const tulun::LOG_LEVEL &level,
                   const std::string &filename,
                   const std::string &funcname,
                   const int line);
        ~logmessage();
        tulun::LOG_LEVEL getlevel()const;
        const std::string tostring()const;
    };
}
#endif