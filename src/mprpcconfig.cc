#include "mprpcconfig.h"
#include <iostream>
#include <fstream>
#include <sstream>
// 记录配置项
void MprpcConfig::LoadConfig(const char* configfile)
{
    // 1.打开配置文件
    std::fstream pf(configfile);
    if (!pf.is_open())
    {
        Logger::GetInstance().Error_Log("open config file error!");
        exit(EXIT_FAILURE);
    }
    std::stringstream configStream;
    configStream << pf.rdbuf();
    // 2.读取配置文件
    std::string line;
    while (std::getline(configStream, line))
    {
        // 3.去掉换行符
        line.erase(line.find_last_not_of("\n") + 1);
        // 4.去掉注释
        if (line[0] == '#')
            continue;
        // 5.分割key和value
        size_t pos = line.find('=');
        if (pos == std::string::npos)
            continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        _configMap[key] = value;
    }
    // 6.关闭文件
    pf.close();
}
//查找对应的配置项
std::string MprpcConfig::Load(const std::string& key)
{
    if(_configMap.count(key) == 0)
    {
        Logger::GetInstance().Error_Log("key is not exist!");
        return "";
    }
    return _configMap[key];
}