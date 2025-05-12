#pragma once
#include <zookeeper/zookeeper.h>
#include <string>
#include <semaphore.h>

class ZkClient
{
public:
    ZkClient();
    ~ZkClient();
    //连接zookeeper
    void Start();
    //创建节点
    void CreateNode(const std::string& path, const char* data,int datalen,int state = 0);
    //获取节点数据
    std::string GetNodeData(const std::string& path);
private:
    zhandle_t* _zhandle; //zookeeper句柄
};