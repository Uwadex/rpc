#include <iostream>
#include "../user.pb.h"
#include <string>
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include "mprpcchannel.h"
#include "logger.h"
int main(int argc,char* argv[])
{
    //调用框架的初始化操作
    MprpcApplication::init(argc,argv);
    //远程调用Login方法
    fixbug::LoginRequest request;
    fixbug::LoginResponse response;
    request.set_name("zhangsan");
    request.set_pwd("123456");
    fixbug::UserService_Stub stub(new MprpcChannel());
    //发起rpc远程调用
    stub.Login(nullptr,&request,&response,nullptr);
    //打印返回结果  
    if(response.success())
    {
        std::cout << "Login success!" << std::endl;
    }
    else
    {
        std::cout << "Login failed!" << std::endl;
    }

    return 0;
}