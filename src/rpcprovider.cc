#include "rpcprovider.h"
#include <google/protobuf/descriptor.h>
// 创建新的rpc服务 
void RpcProvider::NotifyService(google::protobuf::Service* service)
{
    //获取服务名 先获取对整个服务的描述 serviceName=>UserService  
    const google::protobuf::ServiceDescriptor* serviceDesc = service->GetDescriptor();
    std::string serviceName = serviceDesc->name();
    //然后是具体的描述的每一个rpc方法的描述 methodName =>Login 
    for(int i = 0 ;i < serviceDesc->method_count(); ++i)
    {
        //获取每一个rpc方法的描述
        const google::protobuf::MethodDescriptor* methodDesc = serviceDesc->method(i);
        std::string methodName = methodDesc->name();
        //将每一个方法的方法名和方法描述符存入map中
        _serviceMap[serviceName]._methodMap.insert({methodName, methodDesc});
    }
    //存下来服务对象
    _serviceMap[serviceName]._service = service;
}
///启动rpc服务
void RpcProvider::Run()
{
    //获取配置文件中的ip和port
    std::string ip = MprpcApplication::Getconfig().Load("rpcserverip");
    uint16_t port = std::stoi(MprpcApplication::Getconfig().Load("rpcserverport"));
    //创建rpc服务端对象
    muduo::net::InetAddress addr(ip, port);
    muduo::net::TcpServer server(&_eventloop,addr,"RpcProvider");
    //设置回调函数
    server.setConnectionCallback([this](const muduo::net::TcpConnectionPtr& conn)
    {
        
    });
    server.setMessageCallback([this](const muduo::net::TcpConnectionPtr& conn,
        muduo::net::Buffer* buffer,
        muduo::Timestamp time)
    {
        
    });
    //设置线程数 1个处理连接 3个处理信息的交互
    server.setThreadNum(4);
    //启动服务
    server.start();
    _eventloop.loop();
}