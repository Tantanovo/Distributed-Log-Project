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
        static const size_t FILE_BUFF_SIZE = 1024 * 128;
        FILE *fp_;
        std::unique_ptr<char[]> buff_;
        size_t writenbytes_; // file total
        size_t write(const char *msg, const int len);

    public:
        appendfile(const std::string &filename);
        ~appendfile();
        void append(const std::string &mas);
        void append(const char *msg, const int len);
        void flush();
        size_t getwritebytes() const;
    };
}

#endif