//owner
#include "timestamp.hpp"

//c++ stl
#include<iostream>
using namespace std;
int main(){
    tulun::timestamp stamp;
    stamp.now();
    cout<<stamp.toformattedfile()<<endl;
    cout<<stamp.toformattedstring()<<endl;
    cout<<stamp.tostring()<<endl;
    return 0;
}