
#include "asynlogging.hpp"
namespace tulun
{
    void asynlogging::workthreadfunc()
    {
        latch_.countdown();                    // (1) 初始化完成信号
        std::vector<std::string> buffstowrite; // (2) 局部缓冲区，用于批量写入

        while (running_) // (3) 循环，直到收到停止信号
        {
            {
                std::unique_lock<std::mutex> lock(mutex_); // (4) 加锁，保护临界区

                // (5) 如果缓冲区队列为空，则等待1秒或被唤醒
                if (buffers_.empty())
                {
                    cond_.wait_for(lock, std::chrono::seconds(1));
                }

                // (6) 将当前活跃缓冲区移入待写入队列
                buffers_.push_back(std::move(currentbuffer_));

                // (7) 交换缓冲区，将待写入数据取出到局部变量，释放锁
                buffstowrite.swap(buffers_);

                // (8) 为下一轮生产做准备
                buffers_.reserve(buffqueuesize);
                currentbuffer_.reserve(buffmaxlen);
            } // (9) 自动解锁

            // (10) 流量控制：如果待写入缓冲区过多，丢弃中间部分日志
            if (buffstowrite.size() > 25)
            {
                fprintf(stderr, "droppend log message at larget buffers \n");
                buffstowrite.erase(buffstowrite.begin() + 2, buffstowrite.end());
            }

            // (11) 将数据写入文件
            for (const auto &buffer : buffstowrite)
            {
                output_.append(buffer);
            }

            // (12) 清空局部缓冲区
            buffstowrite.clear();
        }
    }
    asynlogging::asynlogging(const std::string &basename,
                             const size_t rollsize,
                             int flushinterval) : flushinterval_(flushinterval),
                                                  running_(false),
                                                  rollsize_(rollsize),
                                                  pthread_(nullptr),
                                                  output_(basename, rollsize),
                                                  latch_(1)
    {
        currentbuffer_.reserve(buffmaxlen);
        buffers_.reserve(buffqueuesize);
    };
    asynlogging::~asynlogging()
    {
        if (running_)
        {
            stop();
        }
    };
    void asynlogging::append(const std::string &msg)
    {
        append(msg.c_str(), msg.size());
    };
    void asynlogging::append(const char *msg, const size_t len)
    {
        std::unique_lock<std::mutex> lock(mutex_); // (1) 加锁

        // (2) 检查当前缓冲区是否有足够空间
        if (currentbuffer_.size() >= buffmaxlen ||
            currentbuffer_.capacity() - currentbuffer_.size() < len)
        {
            buffers_.push_back(std::move(currentbuffer_)); // (3) 空间不足，移交当前缓冲区
            currentbuffer_.reserve(buffmaxlen);            // (4) 准备新的缓冲区
        }
        currentbuffer_.append(msg, len); // (5) 写入数据

        cond_.notify_one(); // (6) 唤醒消费者线程
    };
    void asynlogging::flush()
    {
        std::vector<std::string> buffertowriter;
        std::unique_lock<mutex> lock(mutex_);
        buffers_.push_back(std::move(currentbuffer_));
        buffertowriter.swap(buffers_);
        for (const auto &buffer : buffertowriter)
        {
            output_.append(buffer);
        }
        output_.flush();
        buffertowriter.clear();
        currentbuffer_.reserve(buffmaxlen);
        buffers_.reserve(buffqueuesize);
    };
    void asynlogging::start()
    {
        running_ = true;
        pthread_.reset(new std::thread(&asynlogging::workthreadfunc, this));
        latch_.wait(); // 等待工作线程初始化完成
    };

    void asynlogging::stop()
    {
        running_ = false;
        cond_.notify_all(); // 唤醒可能在等待的工作线程
        if (pthread_->joinable())
        {
            pthread_->join(); // 等待工作线程执行完毕
        }
    };
};
