#pragma once
#include "mprpcconfig.h"
#include "logger.h"
#include "header.pb.h"
#include "rpcprovider.h"
#include "mprpcconfig.h"
class MprpcApplication
{
private:
    MprpcApplication();
    static MprpcConfig _mprpcConfig;
public:
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication& operator=(const MprpcApplication&) = delete;
    MprpcApplication(const MprpcApplication&&) = delete;
    MprpcApplication& operator=(const MprpcApplication&&) = delete;
    static MprpcApplication& Getinstance();
    static MprpcConfig& Getconfig();
    static void init(int argc, char** argv);
};
