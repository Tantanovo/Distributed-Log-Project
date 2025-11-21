
#include "logger.hpp"
#include <stdio.h>

namespace tulun
{
    // class logger{
    //     public:
    // using outputfunc=std::function<void(const std::string &)>;
    // using flushfunc=std::function<void(void)>;

    static tulun::LOG_LEVEL initloglevel()
    {
        if (::getenv("TULUN::LOG_TRACE"))//// 检查是否设置了 TULUN_LOG_TRACE 环境变量
        {
            return tulun::LOG_LEVEL::TRACE;
        }
        else if (getenv("TULUN::LOG_DEBUG"))
        {
            return tulun::LOG_LEVEL::DEBUG;
        }
        else
        {
            return tulun::LOG_LEVEL::INFO;
        }
    }

    void defaultoutput(const std::string &msg)//这个函数将接收到的日志字符串 `msg` 写入到标准输出 `stdout`
    {//使用 `fwrite` 而不是 `printf`，因为 `fwrite` 对于二进制数据或不含格式化字符的字符串来说效率更高。
        size_t n = fwrite(msg.c_str(), sizeof(char), msg.size(), stdout);
    }
    void defaultflush()
    {
        fflush(stdout);
    }
    logger::outputfunc logger::s_output_ = defaultoutput;
    logger::flushfunc logger::s_flush_ = defaultflush;

    void logger::setoutput(outputfunc out)
    {
        s_output_ = out;
    }
    void logger::setflush(flushfunc flush)
    {
        s_flush_ = flush;
    }

    //    tulun::logmessage impl_;

    logger::logger(const tulun::LOG_LEVEL &level,
                   const std::string &filename,
                   const std::string &funcname,
                   const int line) : impl_(level, filename, funcname, line) {

                                     };
    logger::~logger()
    {
        impl_ << "\n";
        s_output_(impl_.tostring());
        s_flush_(); //??
        if (impl_.getlevel() == LOG_LEVEL::FATAL)
        {
            fprintf(stderr, "process exit \n");
            exit(1);
        }
    }
    logmessage &logger::stream()
    {
        return impl_;
    }

    tulun::LOG_LEVEL logger::s_level_ = initloglevel();

    void logger::setloglevel(const tulun::LOG_LEVEL &level)
    {
        s_level_ = level;
    };
    tulun::LOG_LEVEL logger ::getlevel()
    {
        return s_level_;
    };
};