#include <memory>
#include <mutex>
// owner
#include "timestamp.hpp"
#include "appendfile.hpp"
// c++stl
#include <string>
using namespace std;
// c api
#include <time.h>
#ifndef LOGFILE_HPP
#define LOGFILE_HPP
namespace tulun
{
    class logfile
    {
    private:
    // 日志文件的基础名称，例如 "app.log"
        const std::string basename_;
        const size_t rollsize_;   // 超过回滚大小产生新日志
        // 日志刷新到磁盘的时间间隔，单位是秒。
        // 即使日志文件没写满，每隔一段时间也会强制将缓冲区内容写入磁盘，防止数据丢失
        const int flushinterval_; // 3s
         // 执行日志滚动和刷新检查的频率（事件计数）。
        // 为了提高性能，不会每次写入日志都去检查是否需要滚动或刷新。
        // 而是每写入 checkeventn_ 次日志事件后，才进行一次检查。
        const int checkeventn_;   // 25~15
        int count_;// 当前日志事件的计数。

    private:
        // 当前日志文件周期的起始时间戳（秒级）。
        // 用于按时间维度进行日志滚动（例如，每天生成一个新日志文件）。
        // 这个时间通常是日志文件创建时的零点时间。
        time_t start0fperiod_;
        time_t lastroll_; // 上次执行日志滚动操作的时间戳
        time_t lastflush_;// 上次执行日志刷新操作的时间戳。
        static const int krollperseconds_ = 60 * 60 * 24;
        // 这意味着日志文件至少每天会滚动一次，即使文件大小没达到 rollsize_。

    private:
        std::unique_ptr<std::mutex> mutex_; // 互斥锁，用于保证多线程环境下日志写入的线程安全性。
        std::unique_ptr<tulun::appendfile> file_;
        // 指向底层文件追加器的智能指针。
        // logfile 类负责管理日志滚动和刷新策略，而实际的文件写入操作则委托给 appendfile。
        // 这种设计将策略与实现分离，提高了代码的模块化程度。

    private:
        // 【核心私有方法】在不加锁的情况下向文件追加日志。
        // 这个方法是实际的日志写入入口，但它本身不进行线程同步。
        // 它会被公共的 append 方法调用，而公共方法会负责加锁。
        // 这样做的好处是，当调用者能保证线程安全时（例如在单线程环境），可以直接调用此方法以避免锁开销。
        void append_unlocked(const char *msg, const size_t len);
        // 【静态辅助方法】根据基础文件名和当前时间生成一个完整的日志文件名。
        // 例如，basename 为 "app.log"，now 为某个时间点，可能生成 "app.log.20231027-153000"。
        // 这个方法是静态的，因为它不依赖于任何对象的状态。
        static std::string getlogfilename(const std::string &basename,
                                          const tulun::timestamp &now);

    public:
        logfile(const std::string &basename,
                size_t rollsize = 1024 * 128,
                bool threadsafe = true,
                int flushinterval = 3,
                int checkeventn = 20);
        ~logfile();
        void append(const std::string &msg);
        void append(const char *msg, const size_t len);
        void flush();
        bool rollfile();
    };
}

#endif