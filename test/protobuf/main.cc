#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;
int main()
{
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("123456");
    std::string send_str;
    // 对象数据序列化成一个char* 也就是字符串
    if(req.SerializeToString(&send_str))
    {
        std::cout <<  send_str.c_str() << std::endl;
    }
    //send_str 反序列化成一个login请求对象
    LoginRequest req2;
    if(req2.ParseFromString(send_str))
    {
        std::cout << "name: " << req2.name() << std::endl;
        std::cout << "pwd: " << req2.pwd() << std::endl;
    }
    return 0;
}