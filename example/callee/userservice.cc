#include <iostream>
#include "../user.pb.h"
#include <string>
#include "mprpcapplication.h"
#include "rpcprovider.h"
class UserService:public fixbug::UserService
{
public:
    bool Login(const std::string& name,const std::string& pwd)
    {
        std::cout<< "Login: " << name << " " << pwd << std::endl;
        return true;
    }
    void Login(google::protobuf:: RpcController* controller,
        const ::fixbug::LoginRequest* request,
        ::fixbug::LoginResponse* response,
        ::google::protobuf::Closure* done)override
        {
            //取出发出方的请求
            std::string name = request->name();
            std::string pwd = request->pwd();
            bool result = Login(name,pwd);
            //设置返回值
            fixbug::ResultCode* resultcode = response->mutable_result();
            resultcode ->set_errcode(0);
            resultcode ->set_errmsg("ok");
            response->set_success(result);
            //设置回调函数
            done->Run();
        }
};
int main(int argc,char* argv[])
{
    //调用框架的初始化操作
    MprpcApplication::init(argc,argv);
    //创建rpc服务对象
    RpcProvider rpcprovider;
    //注册服务对象
    rpcprovider.NotifyService(new UserService());
    //启动rpc服务
    rpcprovider.Run();
    std::cout << "UserService is running..." << std::endl;
    return 0;
}