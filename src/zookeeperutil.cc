#include "mprpcapplication.h"
#include "zookeeperutil.h"
//全局的watcher观察器
//当这里执行正常时本地才和zookeepr的服务端正式建立连接
void global_watcher(zhandle_t* zh, int type, int state, const char* path,void* watcherCtx)
{
    if(type == ZOO_SESSION_EVENT)
    {
            if(state == ZOO_CONNECTED_STATE)
            {
                sem_t *sem = (sem_t*)zoo_get_context(zh);
                sem_post(sem);
            }
    }
}



ZkClient::ZkClient():_zhandle(nullptr){}


ZkClient::~ZkClient()
{
    if(_zhandle != nullptr)
    {
        zookeeper_close(_zhandle);
    }
}

void ZkClient::Start()
{
    //获取配置文件中的ip和port
    std::string host = MprpcApplication::Getconfig().Load("zookeeperip");
    std::string port = MprpcApplication::Getconfig().Load("zookeeperport");
    std::string connstr = host + ":" + port;
    sem_t sem;
    sem_init(&sem,0,0);
    _zhandle = zookeeper_init(connstr.c_str(),global_watcher,30000,nullptr,nullptr,0);
    if(_zhandle == nullptr)
    {
        Logger::GetInstance().Error_Log("zookeeper init error!");
        return;
    }
    zoo_set_context(_zhandle,&sem);
    sem_wait(&sem);
    std::cout << "zookeeper connect success!" << std::endl;
    //到这里本地和zookeeper的服务端建立连接成功
    Logger::GetInstance().Info_Log("zookeeper connect success!");
}

void ZkClient::CreateNode(const std::string& path, const char * data,int datalen,int state)
{
    char path_buffer[128];
    int buffer_len = sizeof(path_buffer);
    //创建节点
    int flag = zoo_exists(_zhandle,path.c_str(),0,0);
    if(flag == ZNONODE)
    {
        //创建节点
        int ret = zoo_create(_zhandle,path.c_str(),data,datalen,&ZOO_OPEN_ACL_UNSAFE,state,path_buffer,buffer_len);
        if(ret == ZOK)
        {
            Logger::GetInstance().Info_Log("create node success!");
        }
        else
        {
            Logger::GetInstance().Error_Log("create node error!");
        }
    }
}

std::string ZkClient::GetNodeData(const std::string& path)
{
    char buffer[128];
    int buffer_len = sizeof(buffer);
    int flag = zoo_get(_zhandle,path.c_str(),0,buffer,&buffer_len,nullptr);
    if(flag == ZOK)
    {
        std::string data(buffer);
        return data;
    }
   
    return "";
}