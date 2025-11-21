// 提供时间戳相关功能，比如获取当前时间、将时间格式化为字符串（如 “年 - 月 - 日 时：分: 秒”），用于给日志打时间标记
#ifndef timestamp_hpp
#define timestamp_hpp
// c++ stl
#include <string>
using namespace std;
#include <bits/types.h>
// owner
#include "logcommon.hpp"
namespace tulun
{
    class timestamp : public tulun::copytable
    {
    private:
        uint64_t micro_;

    public:
        timestamp();
        timestamp(uint64_t m);
        ~timestamp();
        void swap(timestamp &other);
        std::string tostring() const;
        // ssss.mmm;
        std::string toformattedstring(bool showmicro = true) const;

        std::string toformattedfile() const;

        bool vaild() const;
        uint64_t getmicro() const;
        uint64_t getsecond() const;
        const timestamp &now();
        operator u_int64_t() const;

    public:
        static timestamp Now();
        static timestamp invaild();
        static const int kmircoperseconds = 1000 * 1000;
    };
}

#endif