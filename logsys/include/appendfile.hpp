//这份头文件定义了一个用于高效地向文件追加数据的类。
//它是日志系统中一个非常关键的组件，通常被用作日志输出的目的地（例如，将日志写入磁盘文件）。
// c++ stl
#include <memory>
#include <string>
// c API
#include <stdio.h>
#ifndef APPENDFILE_HPP
#define APPENDFILE_HPP
namespace tulun
{
    class appendfile
    {
    private:
        static const size_t FILE_BUFF_SIZE = 1024 * 128;//定义内存缓冲区的大小
        FILE *fp_;//指向C标准库文件流的指针
        std::unique_ptr<char[]> buff_;//智能指针，管理动态分配的字符数组作为内存缓冲区。
        size_t writenbytes_; // file total  记录当前缓冲区中已写入的数据长度（字节数）。
        size_t write(const char *msg, const int len);//将数据从缓冲区写入到文件的内部辅助函数。

    public:
        appendfile(const std::string &filename);
        ~appendfile();
        void append(const std::string &msg);//这是一个对外的公共接口，它会将数据先写入内部缓冲区。
        void append(const char *msg, const int len);//这是另一个对外的公共接口，提供了更底层的控制，适用于已经获取了字符指针和长度的场景。
        void flush();
        size_t getwritebytes() const;
    };
}

#endif