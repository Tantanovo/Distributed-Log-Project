// owner
#include "timestamp.hpp"
#include "logmessage.hpp"
#include "logger.hpp"
// c++ stl
#include<appendfile.hpp>
#include <iostream>
#include"logfile.hpp"
using namespace std;

tulun::appendfile appfile("yhping.log");
void appoutput(const std::string &msg){
    appfile.append(msg);
}
void appflush(){
    appfile.flush();
}








void func()
{
    LOG_TRACE << "in func";
    for (int i = 0; i < 10; i++)
    {
        LOG_INFO << i;
    }
    LOG_TRACE << "out func";
}
int main()
{   tulun::logger::setoutput(appoutput);
    tulun::logger::setflush(appflush);
    tulun::logger::setloglevel(tulun::LOG_LEVEL::TRACE);
           
         LOG_TRACE<< "in main";
         LOG_TRACE<< "exit main";

    return 0;
}
#if 0

int main(){
    LOG_TRACE<<"yhping"<<1;
    LOG_EDBUG<<"yhping"<<2;
    LOG_INFO<<"yhping"<<3;
    LOG_WARN<<"yhping"<<4;
    LOG_ERROR<<"yhping"<<5;
    LOG_FATAL<<"yhping"<<6;
    LOG_INFO<<"info:"<<7;

    return 0;
}

int main(){
    tulun::logger log(tulun::LOG_LEVEL::DEBUG,
                        __FILE__,__func__,__LINE__);
    log.stream()<<"yhping";
    log.stream()<<23;
    return 0;
}

#endif

#if 0
int main(){
    tulun::logmessage logmes(tulun::LOG_LEVEL::DEBUG,
                            __FILE__,__func__,__LINE__);
    logmes<<"yhping";
    logmes<<23;
    cout<<logmes.tostring()<<endl;
    return 0;
}
#endif

#if 0

int main(){
    
    tulun::timestamp stamp;
    stamp.now();
    cout<<stamp.toformattedfile()<<endl;
    cout<<stamp.toformattedstring()<<endl;
    cout<<stamp.tostring()<<endl;
    return 0;
}

#endif