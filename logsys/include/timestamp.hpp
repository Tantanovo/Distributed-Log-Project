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
        timestamp(uint64_t m);//用一个已知的微秒数来构造一个时间戳对象。这在反序列化或从其他时间表示转换时非常有用。
        ~timestamp();
        void swap(timestamp &other);//交换两个 timestamp 对象的内容。
        std::string tostring() const;//将时间戳格式化为 "秒.微秒" 的字符串形式。
        // ssss.mmm;
        std::string toformattedstring(bool showmicro = true) const;//将时间戳格式化为人类可读的字符串形式。

        std::string toformattedfile() const;//将时间戳格式化为适合作为文件名的字符串

        bool vaild() const;//检查当前时间戳对象是否有效。
        uint64_t getmicro() const;//微秒
        uint64_t getsecond() const;//秒
        const timestamp &now();//更新当前对象为当前系统时间
        operator u_int64_t() const;// 类型转换运算符，允许将 timestamp 对象隐式转换为 uint64_t

    public:
        static timestamp Now();//获取一个代表当前系统时间的 timestamp 对象
        static timestamp invaild();//获取一个无效的 timestamp 对象。
        static const int kmircoperseconds = 1000 * 1000;//一个常量，表示一秒钟包含的微秒数（1,000,000）
    };
}

#endif