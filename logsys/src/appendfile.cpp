#include "appendfile.hpp"
#include <string.h>
#include <cassert>
namespace tulun
{ /*
*  内部辅助函数，将数据直接写入文件流。
* 这个函数是 `appendfile` 类性能优化的关键。它使用了 `fwrite_unlocked` 而不是 `fwrite`。
* `fwrite_unlocked` 是线程不安全的版本，但它执行速度更快，因为它省去了线程同步的开销。
* 在 `appendfile` 类的设计中，线程安全是由使用它的上层调用者（如日志系统）来保证的，
* 因此这里可以安全地使用 unlocked 版本来获得性能提升。
*  msg 指向要写入数据的指针。
*  len 要写入数据的长度（字节数）。
 return 返回实际写入的字节数。*/
    size_t appendfile::write(const char *msg, const int len)
    {
        return fwrite_unlocked(msg, sizeof(char), len, fp_);
        // fwrite
    }

    appendfile::appendfile(const std::string &filename)
        : fp_{nullptr},
          buff_{new char[FILE_BUFF_SIZE]},
          writenbytes_(0)// 初始化缓冲区已使用字节数为 0
    {// 以追加模式打开文件。"a" 表示如果文件存在，则在末尾追加；如果不存在，则创建。
        fp_ = fopen(filename.c_str(), "a");
        assert(fp_ != nullptr);
        // 这是一个非常关键的调用。它告诉 C 标准库，不要使用它自己的缓冲区，
        // 而是使用我们提供的 buff_ 指向的内存作为该文件流的缓冲区。
        // 这样，所有对该文件流的写入操作都会先写入到我们的缓冲区中，
        // 直到缓冲区满了或者我们手动调用 fflush，数据才会被真正写入磁盘。
        setbuffer(fp_, buff_.get(), FILE_BUFF_SIZE);
    };
    appendfile::~appendfile()
    {
        fclose(fp_);
        fp_ = nullptr;
        // 智能指针 buff_ 会在其生命周期结束时（即 appendfile 对象销毁时）自动释放所管理的内存，
        // 所以这里不需要手动 delete。
        buff_.reset();// reset() 会释放当前指向的内存，并将指针置为 nullptr。
                       // 在析构函数中，这一步不是必须的，但写出来可以让意图更清晰。
    };
<<<<<<< HEAD
    void appendfile::append(const std::string &msg)//c++接口
    {
        append(msg.c_str(), msg.size());
    };
    void appendfile::append(const char *msg, const int len)//c接口

    void appendfile::append(const std::string &msg)
    {
        append(msg.c_str(), msg.size());
    };
    void appendfile::append(const char *msg, const int len)

    {
        size_t n = write(msg, len); // 记录已经成功写入的字节数
        size_t remain = len - n;// 计算剩余多少字节需要写入
        while (remain > 0)// 循环，直到所有数据都被写入
        { // 尝试写入剩余的数据
            size_t x = write(msg + n, remain);
            if (0 == x)// 如果写入的字节数为 0，说明可能发生了错误
            {// 获取具体的错误码
                int err = ferror(fp_);
                if (err)
                {// 打印错误信息到标准错误输出
                    fprintf(stderr, "appendfile::append() failed %s \n",
                            strerror(err));
                    break;
                }
            }
            n += x;// 更新已写入字节数和剩余字节数
            remain = len - n;
        }// 注意：这里的 writenbytes_ 统计的是逻辑上写入文件的字节数，
        // 实际这些数据可能还在内存缓冲区中，并未真正写入磁盘。
        writenbytes_ += n;
    };
    void appendfile::flush()// 将文件流的缓冲区（这里是我们设置的 buff_）中的数据强制刷新到磁盘文件。
    {//这是一个同步点，会有性能开销，但能保证数据的持久性。
        fflush(fp_);
    };
    size_t appendfile::getwritebytes() const
    {
        return writenbytes_;
    };

}