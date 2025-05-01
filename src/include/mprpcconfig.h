#pragma once
#include <unordered_map>
class MprpcConfig
{
public:
    void LoadConfig(const char* configfile);
    std::string Load(const std::string& key);
private:
    std::unordered_map<std::string, std::string> _configMap;
};