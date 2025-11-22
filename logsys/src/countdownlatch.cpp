#include "countdownlatch.hpp"
namespace tulun
{
    countdownlatch::countdownlatch(int count) : count_(count) {

                                                };
    void countdownlatch::wait()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ > 0)
        {
            cond_.wait(lock);
        }
    };
    void countdownlatch::countdown()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        count_ -= 1;
        if (count_ == 0)
        {
            cond_.notify_all();
        }
    };
    int countdownlatch::getcount() const
    {
        return count_;
    }

};
