// 这是一个 C++ 实现的倒计时门闩（Countdown Latch）同步工具，
// 它允许一个或多个线程等待，直到其他线程完成一系列操作
#include<condition_variable>
#include<mutex>
using namespace std;

#ifndef COUNT_DOWN_LATCH_HPP
#define COUNT_DOWN_LATCH_HPP

namespace tulun{
    class countdownlatch{
        private:
            int count_;                     // 倒计时计数器
            std::condition_variable cond_;  // 条件变量，用于线程等待/通知
            std::mutex mutex_;              // 互斥锁，保护共享变量count_

        public:
            countdownlatch(int count);      // 构造函数，初始化倒计时次数
            void wait();                    // 等待倒计时归零
            void countdown();               // 倒计时减1
            int getcount()const;            // 获取当前倒计时数值
    };
}

#endif