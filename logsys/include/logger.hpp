
#include <functional>
#include <string>
// owner
#include "logmessage.hpp"
#ifndef LOGGER_HPP
#define LOGGER_HPP
namespace tulun
{
    class logger
    {
    public://这是一个函数对象，它接受一个 const std::string& 类型的参数（即完整的日志字符串），
         //并且没有返回值。用户可以通过 setoutput() 方法自定义日志的输出方式，
        using outputfunc = std::function<void(const std::string &)>;
        using flushfunc = std::function<void(void)>;

        static outputfunc s_output_;// 所有的 logger 实例都会使用这个全局函数来输出日志。
        static flushfunc s_flush_;// 所有的 logger 实例都会使用这个全局函数来刷新日志。

        static void setoutput(outputfunc);//设置全局的日志输出函数。
        static void setflush(flushfunc);//设置全局的日志刷新函数。

    private:
        tulun::logmessage impl_;//一个 logmessage 对象，负责实际的日志内容构建。

    public:
        logger(const tulun::LOG_LEVEL &level,
               const std::string &filename,
               const std::string &funcname,
               const int line);
        ~logger();
        logmessage &stream();

    private:
        static tulun::LOG_LEVEL s_level_;//静态成员变量，存储全局的日志级别。

    public:
        static void setloglevel(const tulun::LOG_LEVEL &level);
        static tulun::LOG_LEVEL getlevel();
    };
#define LOG_TRACE                                             \
    if (tulun::logger::getlevel() <= tulun::LOG_LEVEL::TRACE) \
    tulun::logger(tulun::LOG_LEVEL::TRACE, __FILE__, __func__, __LINE__).stream()
#define LOG_DEBUG                                             \
    if (tulun::logger::getlevel() <= tulun::LOG_LEVEL::DEBUG) \
    tulun::logger(tulun::LOG_LEVEL::DEBUG, __FILE__, __func__, __LINE__).stream()
#define LOG_INFO                                             \
    if (tulun::logger::getlevel() <= tulun::LOG_LEVEL::INFO) \
    tulun::logger(tulun::LOG_LEVEL::INFO, __FILE__, __func__, __LINE__).stream()
#define LOG_WARN \
    tulun::logger(tulun::LOG_LEVEL::WARN, __FILE__, __func__, __LINE__).stream()
#define LOG_ERROR \
    tulun::logger(tulun::LOG_LEVEL::ERROR, __FILE__, __func__, __LINE__).stream()
#define LOG_FATAL \
    tulun::logger(tulun::LOG_LEVEL::FATAL, __FILE__, __func__, __LINE__).stream()
}
#endif