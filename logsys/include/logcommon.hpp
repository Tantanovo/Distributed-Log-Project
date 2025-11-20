//定义日志系统的通用类型、枚举或工具函数，比如日志级别（DEBUG、INFO、ERROR 等）、字符串格式化工具等。
#ifndef log_common_hpp
#define log_common_hpp
namespace tulun{
    static const int small_buff_len=128;
    static const int middle_buff_len=512;
    static const int large_buff_len=1024;
    enum class LOG_LEVEL{
        TRACE=0,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVENS
    };
    extern const char *LLTOSTR[];
    
    struct copytable{
        copytable() = default;
        copytable(const copytable &)=default;
        copytable &operator=(const copytable &)=default;
    };
    struct notcopy{
        notcopy(const notcopy &)=default;
        notcopy &operator=(const notcopy &)=default;
    };
}
#endif