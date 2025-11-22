#include <atomic>
#include <string>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

// 倒计时门闩，用于线程同步，确保工作线程启动完成
#include"countdownlatch.hpp"
// 日志文件类，负责日志的滚动、写入文件等操作
#include "logfile.hpp"

#ifndef ASYNLOGGING_HPP
#define ASYNLOGGING_HPP

namespace tulun
{
    class asynlogging
    {
    private:
        // 工作线程函数，消费者线程的核心逻辑
        void workthreadfunc();

    private:
        const int flushinterval_; // 日志刷盘间隔（秒），定时将缓冲区数据写入文件
        std::atomic<bool> running_; // 原子变量，标记日志系统是否正在运行
        const std::string basename_; // 日志文件基础名称
        const size_t rollsize_; // 日志文件滚动大小阈值，超过该大小则创建新文件
        std::unique_ptr<std::thread> pthread_; // 工作线程（消费者线程）
        std::mutex mutex_; // 互斥锁，保护缓冲区队列的线程安全
        std::condition_variable cond_; // 条件变量，用于线程间通信（生产者唤醒消费者）
        std::string currentbuffer_; // 当前日志缓冲区（生产者线程使用）
        std::vector<std::string> buffers_; // 待写入文件的缓冲区队列（消费者线程处理）
        tulun::logfile output_; // 日志文件操作对象，负责实际的文件写入
        tulun::countdownlatch latch_; // 倒计时门闩，用于主线程等待工作线程初始化完成
        
        static const size_t buffmaxlen; // 单个缓冲区最大长度（4KB）
        static const size_t buffqueuesize; // 缓冲区队列最大容量（16个缓冲区）

    public:
        // 构造函数
        // 参数：basename-日志文件基础名，rollsize-文件滚动大小，flushinterval-刷盘间隔
        asynlogging(const std::string &basename,
                    const size_t rollsize = 1024 * 128,  // 默认128KB滚动
                    int flushinterval = 3); // 默认3秒刷盘一次
        ~asynlogging(); // 析构函数，停止日志系统并释放资源
        
        // 日志写入接口（字符串版本）
        void append(const std::string &msg);
        // 日志写入接口（字符数组版本，更高效）
        void append(const char *msg, const size_t len);
        
        // 手动触发日志刷盘（将缓冲区数据写入文件）
        void flush();
        // 启动日志系统（创建并启动工作线程）
        void start();
        // 停止日志系统（安全退出工作线程）
        void stop();
    };

}

#endif