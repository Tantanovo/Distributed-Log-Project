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
    const char *LLTOSTR[]={
        "TRACE",//0
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR",
        "FATAL",
        "NUM_LOG_LEVENS"
    };
    struct copytable{
        copytable(copytable &){}
        copytable &operator=(const copytable &){
            return *this;
        }
    };
    struct notcopy{
        notcopy(const notcopy &)=delete;
        notcopy &operator=(const notcopy &)=delete;
    };
}
#endif