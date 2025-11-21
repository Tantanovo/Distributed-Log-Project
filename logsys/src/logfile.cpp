#include "logfile.hpp"
#include "logcommon.hpp"
// linux
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
namespace tulun
{
    // class logfile
    // {
    // // private:
    //     const std::string basename_;
    //     const size_t rollsize_;   // 超过回滚大小产生新日志
    //     const int flushinterval_; // 3s
    //     const int checkeventn_;   // 25~15
    //     int count_;

    // private:
    //     time_t start0fperiod_;
    //     time_t lastroll_;
    //     time_t lastflush_;
    //     static const int krollperseconds_ = 60 * 60 * 24;

    // private:
    //     std::unique_ptr<std::mutex> mutex_;
    //     std::unique_ptr<tulun::appendfile> file_;
    pid_t pid()// 获取当前进程 ID
    {
        return ::getpid();
    }
    const std::string hostname()   // 获取主机名
    {
        char buff[tulun::small_buff_len] = {0};// 栈上分配缓冲区，大小从 logcommon 定义
        if (::gethostname(buff, small_buff_len))// 调用系统函数获取主机名
        {
            return std::string(buff); // 成功则返回主机名字符串
        }
        else
        {
            return std::string("noknownhost");
        }
    }
    void logfile::append_unlocked(const char *msg, const size_t len)
    {
        file_->append(msg, len); // 调用 appendfile 写入日志内容
         // 检查当前日志文件大小是否超过滚动阈值
        if (file_->getwritebytes() > rollsize_)
        {
            rollfile();
        }
        else
        {
            count_ += 1;
            if (count_ >= checkeventn_)// 检查是否达到检查频率
            {
                count_ = 0;// 重置计数
                time_t now = ::time(nullptr);// 获取当前时间戳
                // 计算当前周期的起始时间（按天对齐）
                time_t thisperiod = (now / krollperseconds_) * krollperseconds_;
                if (thisperiod != start0fperiod_)
                {
                    rollfile();
                }
                // 检查是否超过刷新间隔
                else if (now - lastflush_ > flushinterval_)
                {
                    lastflush_ = now; // 更新最后刷新时间
                    file_->flush();// 触发缓冲区刷新到磁盘
                }
            }
        }
    };
     // 生成日志文件名（静态函数）
    std::string logfile::getlogfilename(const std::string &basename,
                                        const tulun::timestamp &now)
    {
        std::string filename;
        filename.reserve(basename.size() + tulun::small_buff_len);
        filename = (basename + ".");
        filename += (now.toformattedfile() + ".");
        filename += (hostname() + ".");
        std::stringstream ss;
        ss << tulun::pid();
        filename += ss.str();
        filename += ".log";
        return filename;
    };

    logfile::logfile(const std::string &basename,
                     size_t rollsize,
                     bool threadsafe,
                     int flushinterval,
                     int checkeventn) : basename_(basename),
                                        rollsize_(rollsize),
                                        flushinterval_(flushinterval),
                                        checkeventn_(checkeventn),
                                        count_(0),
                                        mutex_{threadsafe ? new std::mutex : nullptr},
                                        start0fperiod_{0},
                                        lastroll_{0},
                                        lastflush_{0} {

                                        };
    logfile::~logfile() {

    };
    // 追加字符串类型日志（重载）
    void logfile::append(const std::string &msg)
    {
        append(msg.c_str(), msg.size());
    };
     // 追加字符数组类型日志（核心接口）
    void logfile::append(const char *msg, const size_t len)
    {
        if (mutex_)
        {
            std::unique_lock<std::mutex> lock(*mutex_);// RAII 方式加锁，自动释放
            append_unlocked(msg, len);// 调用不加锁的内部函数
        }
        else
        {
            append_unlocked(msg, len);
        }
    };
    void logfile::flush()
    {
        file_->flush();
    };
    bool logfile::rollfile()
    {
        tulun::timestamp now;
        now.now(); // 获取当前时间
        std::string filename = getlogfilename(basename_, now); // 生成新文件名
        // 计算当前周期起始时间（按天对齐）
        time_t start = (now.getsecond() / krollperseconds_) * krollperseconds_;
        if (now.getsecond() > lastroll_)
        {
            lastroll_ = now.getsecond();// 更新最后滚动时间
            lastflush_ = now.getsecond();// 同时更新最后刷新时间
            start0fperiod_ = start;// 更新当前周期起始时间
            file_.reset(new tulun::appendfile(filename));// 创建新的日志文件
            return true;
        }
        return false;
    };
};
