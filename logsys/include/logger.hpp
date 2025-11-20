
#include<functional>
#include<string>
//owner
#include"logmessage.hpp"
#ifndef LOGGER_HPP
#define LOGGER_HPP
namespace tulun{
    class logger{
        public:
            using outputfunc=std::function<void(const std::string &)>;
            using flushfunc=std::function<void(void)>;

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
}
#endif