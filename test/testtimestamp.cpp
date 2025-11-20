//owner
#include "timestamp.hpp"
#include"logmessage.hpp"
#include"logger.hpp"
//c++ stl
#include<iostream>
using namespace std;

int main(){
    tulun::logger log(tulun::LOG_LEVEL::DEBUG,
                        __FILE__,__func__,__LINE__);
    log.stream()<<"yhping";
    log.stream()<<23;
    return 0;
}





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