#include "rpcprovider.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/callback.h>
#include "header.pb.h"
#include "zookeeperutil.h"
// 创建新的rpc服务 
void RpcProvider::NotifyService(google::protobuf::Service* service)
{
    //获取服务名 先获取对整个服务的描述 serviceName=>UserService  
    const google::protobuf::ServiceDescriptor* serviceDesc = service->GetDescriptor();
    std::string serviceName = serviceDesc->full_name();
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
    //像zookeeper中注册服务
    serviceName = "/" + serviceName;
    ZkClient zkclient;
    zkclient.Start();
    //创建父目录
    zkclient.CreateNode(serviceName,nullptr,0);
    for(int i = 0 ;i < serviceDesc->method_count(); ++i)
    {
        const google::protobuf::MethodDescriptor* methodDesc = serviceDesc->method(i);
        std::string methodName = methodDesc->name();
        methodName = serviceName + "/" + methodName;
        //存储信息的格式为ip:port
        std::string msg = MprpcApplication::Getconfig().Load("rpcserverip") + ":" + MprpcApplication::Getconfig().Load("rpcserverport");
        zkclient.CreateNode(methodName,msg.c_str(),msg.size());
    }
}
///启动rpc服务
void RpcProvider::Run()
{
    //获取配置文件中的ip和port
    std::string ip = MprpcApplication::Getconfig().Load("rpcserverip");
    int32_t port = std::stoi(MprpcApplication::Getconfig().Load("rpcserverport"));
    //创建rpc服务端对象
    muduo::net::InetAddress addr(ip, port);
    Logger::GetInstance().Info_Log("rpc server start!");
    muduo::net::TcpServer server(&_eventloop,addr,"RpcProvider");
    //设置回调函数
    //处理连接断开的的情况即可 释放套接字资源
    server.setConnectionCallback([this](const muduo::net::TcpConnectionPtr& conn)
    {
        if(!conn-> connected())
        {
            conn->shutdown();//释放套接字资源
        }
    });
    //处理建立连接之后套接字的信息交互
    //约定好信息交互的信息规范 
    //首先是head信息 包括head信息的长度(前面4个字节记录后面3个信息的长度)和serviceName 和methodName 以及args_size
    //这样就可以拆分成两部分 一个是专门的head信息 一个是args信息
    //通过前面的serviceName和methodName就可以找到对应的服务对象和方法描述符
    server.setMessageCallback([this](const muduo::net::TcpConnectionPtr& conn,
        muduo::net::Buffer* buffer,
        muduo::Timestamp time)
    {
        std::string msg = buffer->retrieveAllAsString();//获取buffer中的所有信息
        std::cout << msg << std::endl;
        int32_t header_size = *((int32_t*)(msg.c_str()));//获取前4个字节的存储的值
        fixbug::header head;
        std::string headbuf = msg.substr(4, header_size);
        //反序列化得到header信息
        if(!head.ParseFromString(headbuf))
        {
            Logger::GetInstance().Error_Log("header parse error!");
            return;
        }

        std::string argsbuf = msg.substr(4 + header_size, head.args_size());
        std::string serviceName = head.servicename();
        std::string methodName = head.methodname();
        //检查map映射表中是否有对应的serviceName和methodName
        if(!_serviceMap.count(serviceName))
        {
            Logger::GetInstance().Error_Log("service is not exist!");
            return;
        }
        auto it  = _serviceMap[serviceName];
        if(it._methodMap.count(methodName) == 0)
        {
            Logger::GetInstance().Error_Log("method is not exist!");
            return;
        }
        auto mit = it._methodMap[methodName];
        google::protobuf::Service* service = it._service;
        //创建rpc方法的参数列表
        google::protobuf::Message* request = service->GetRequestPrototype(mit).New();
        google::protobuf::Message* response = service->GetResponsePrototype(mit).New();
        //反序列化args信息
        if(!request->ParseFromString(argsbuf))
        {
            Logger::GetInstance().Error_Log("args parse error!");
            return;
        }
        //生成done对象 来进行response的反馈
        google::protobuf::Closure* done = google::protobuf::NewCallback<RpcProvider,const muduo::net::TcpConnectionPtr&,google::protobuf::Message*>
        (this,&RpcProvider::SendRpcResponse,conn,response); 
           
        service->CallMethod(mit,nullptr,request,response, done);
    });
    //设置线程数 1个处理连接 3个处理信息的交互
    server.setThreadNum(4);
    //启动服务
    server.start();
    _eventloop.loop();
}
void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr& conn,google::protobuf::Message* response)
{
    std::string response_buf;
    if(response->SerializeToString(&response_buf))
    {
        conn->send(response_buf);
    }   
    else 
    {
        Logger::GetInstance().Error_Log("response serialize error!");
    }
    conn->shutdown();
}