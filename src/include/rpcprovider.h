#pragma once
#include "google/protobuf/service.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>
#include <unordered_map>
#include <string>
#include "mprpcapplication.h"
class RpcProvider
{
public:
    // 提供给外部的发布rpc方法的api接口
    void NotifyService(google::protobuf::Service* service);
    //启动rpc服务
    void Run();
private:
    muduo::net::EventLoop _eventloop; //事件循环
    struct ServiceInfo
    {
        google::protobuf::Service* _service; //服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> _methodMap; //方法名和方法描述符的映射关系
    };
    std::unordered_map<std::string, ServiceInfo> _serviceMap; //服务名和服务对象的映射关系
};