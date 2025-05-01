#include "mprpcapplication.h"
 #include <unistd.h>
 #include <iostream>
 #include <string>
MprpcApplication::MprpcApplication() {}
//类外实例化静态变量
MprpcConfig MprpcApplication::_mprpcConfig;

void ShowArgsHelp()
{
    std::cout << "Usage: ./rpcapplication -i <configfile>" << std::endl;
}

MprpcApplication& MprpcApplication::Getinstance()
{
    static MprpcApplication instance;
    return instance;
}
void MprpcApplication::init(int argc, char** argv)
{
    if(argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }
    int c = 0;
    std::string configfile;
    while((c = getopt(argc,argv,"i:")) != -1)
    {
        switch(c)
        {
            case 'i':
                configfile = optarg;
                break;
            case '?':
                std::cout << "invalid args!" << std::endl;
                ShowArgsHelp();
                exit(EXIT_FAILURE);
            case ':':
                std::cout << "need <configfile>" << std::endl;
                ShowArgsHelp();
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }
    //加载配置文件
    _mprpcConfig.LoadConfig(configfile.c_str());
    //获取配置项
    std::cout<< "rpcserverip: " << _mprpcConfig.Load("rpcserverip") << std::endl;
    std::cout<< "rpcserverport: " << _mprpcConfig.Load("rpcserverport") << std::endl;
    std::cout<< "zookeeperip: " << _mprpcConfig.Load("zookeeperip") << std::endl; 
    std::cout<< "zookeeperport: " << _mprpcConfig.Load("zookeeperport") << std::endl;  
}