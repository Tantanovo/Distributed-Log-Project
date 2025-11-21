// 定义日志消息的结构，比如包含日志级别、时间戳、日志内容、线程 ID 等信息，是日志数据的载体。
#ifndef logmessage_hpp
#define logmessage_hpp
// c++ stl
#include <string>
#include <sstream>
using namespace std;
// owner
#include "logcommon.hpp"

namespace tulun
{
    class logmessage
    {/**
         *  存储日志的“头部”信息。
         * 头部信息通常包括：
         *  - 时间戳
         *  - 日志级别
         *  - 线程ID
         *  - 文件名、函数名、行号
         *
         * 这些信息通常在对象构造时就被格式化并固定下来。
         */
        std::string head_;
        std::string test_;//存储日志的“正文”内容。
        tulun::LOG_LEVEL level_;//存储日志的级别。

    public:/* @param level 日志的级别 (例如 LOG_INFO, LOG_ERROR)。
         * @param filename 日志产生的源文件名 (__FILE__ 宏)。
         * @param funcname 日志产生的函数名 (__func__ 宏)。
         * @param line 日志产生的源代码行号 (__LINE__ 宏)。
         */
        logmessage(const tulun::LOG_LEVEL &level,
                   const std::string &filename,
                   const std::string &funcname,
                   const int line);
        ~logmessage();
        tulun::LOG_LEVEL getlevel() const;
        const std::string tostring() const;
        template <class T>
        logmessage &operator<<(const T &val)
        {
            std::stringstream ss;
            ss << " : " << val;
            test_ += ss.str();
            return *this;
        }
    };
}
#endif