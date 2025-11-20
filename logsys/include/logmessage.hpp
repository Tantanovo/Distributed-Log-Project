//定义日志消息的结构，比如包含日志级别、时间戳、日志内容、线程 ID 等信息，是日志数据的载体。
#ifndef logmessage_hpp
#define logmessage_hpp
//c++ stl
#include<string>
#include<sstream>
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
        template<class T>
        logmessage & operator<<(const T &val){
            std::stringstream ss;
            ss<<" : "<<val;
            test_+=ss.str();
            return *this;
        }
    };
}
#endif