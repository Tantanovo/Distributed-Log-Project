#include "logcommon.hpp"
#include "timestamp.hpp"
// c api
#include <time.h> //time 秒级
// linux api
#include <sys/time.h>

namespace tulun
{
    // class timestamp{
    // uint64_t micro_;

    timestamp::timestamp() : micro_(0) {}
    timestamp::timestamp(uint64_t ms) : micro_(ms) {};
    timestamp::~timestamp() {};
    void timestamp::swap(timestamp &other)
    {
        std::swap(this->micro_, other.micro_);
    };
    std::string timestamp::tostring() const
    {
        char buff[small_buff_len] = {0};
        time_t sec = micro_ / kmircoperseconds;//秒
        time_t mir = micro_ % kmircoperseconds;//微秒
        sprintf(buff, "%ld.%ld", sec, mir);
        return std::string(buff);
    };
    // ssss.mmm;
    std::string timestamp::toformattedstring(bool showmicro) const
    {
        char buff[small_buff_len] = {0};
        time_t sec = micro_ / kmircoperseconds;
        time_t mir = micro_ % kmircoperseconds;
        struct tm t_tm;
        localtime_r(&sec, &t_tm);//时间转换 
<<<<<<< HEAD
        // gmtime_r(&sec,&t_tm);//格林尼治

        // gmtime_r(&sec,&t_tm);

        int len = sprintf(buff, "%04d/%02d/%02d-%02d:%02d:%02d", t_tm.tm_year + 1900,
                          t_tm.tm_mon + 1,
                          t_tm.tm_mday,
                          t_tm.tm_hour,
                          t_tm.tm_min,
                          t_tm.tm_sec);
        if (showmicro)// 如果需要显示微秒，则在后面追加
        {// buff + len 表示从缓冲区的当前末尾继续写入
            sprintf(buff + len, ".%ldZ", mir);// Z 表示祖鲁时间 (UTC)，但这里实际是本地时间
        }
        return std::string(buff);
    };

    std::string timestamp::toformattedfile() const
    {
        char buff[small_buff_len] = {0};
        time_t sec = micro_ / kmircoperseconds;
        time_t mir = micro_ % kmircoperseconds;
        struct tm t_tm;
        localtime_r(&sec, &t_tm);
        // gmtime_r(&sec,&t_tm);
        int len = sprintf(buff, "%04d%02d%02d-%02d%02d%02d", t_tm.tm_year + 1900,
                          t_tm.tm_mon + 1,
                          t_tm.tm_mday,
                          t_tm.tm_hour,
                          t_tm.tm_min,
                          t_tm.tm_sec);
        return std::string(buff);
    };

    bool timestamp::vaild() const
    {
        return micro_ > 0;
    };
    uint64_t timestamp::getmicro() const
    {
        return micro_;
    };
    uint64_t timestamp::getsecond() const
    {
        return (micro_ / kmircoperseconds);
    };
    const timestamp &timestamp::now()
    {
        *this = Now();
        return *this;
    };
    timestamp::operator u_int64_t() const
    {
        return micro_;
    };

    timestamp timestamp::Now()
    {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        uint64_t seconds = tv.tv_sec;

        return timestamp(seconds * kmircoperseconds + tv.tv_usec);
        // 1970 .1,1 000 ---->
        // time;1970. 1 1. 0 0 0--->
    };
    timestamp timestamp::invaild()
    {
        return timestamp();
    };
}