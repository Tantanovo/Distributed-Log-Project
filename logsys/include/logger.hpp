
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
    public:
        using outputfunc = std::function<void(const std::string &)>;
        using flushfunc = std::function<void(void)>;

        static outputfunc s_output_;
        static flushfunc s_flush_;

        static void setoutput(outputfunc);
        static void setflush(flushfunc);

    private:
        tulun::logmessage impl_;

    public:
        logger(const tulun::LOG_LEVEL &level,
               const std::string &filename,
               const std::string &funcname,
               const int line);
        ~logger();
        logmessage &stream();

    private:
        static tulun::LOG_LEVEL s_level_;

    public:
        static void setloglevel(const tulun::LOG_LEVEL &level);
        static tulun::LOG_LEVEL getlevel();
    };
#define LOG_TRACE                                             \
    if (tulun::logger::getlevel() <= tulun::LOG_LEVEL::TRACE) \
    tulun::logger(tulun::LOG_LEVEL::TRACE, __FILE__, __func__, __LINE__).stream()
#define LOG_EDBUG                                             \
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