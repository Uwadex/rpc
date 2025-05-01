#pragma once

class MprpcApplication
{
private:
    MprpcApplication();
public:
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication& operator=(const MprpcApplication&) = delete;
    MprpcApplication(const MprpcApplication&&) = delete;
    MprpcApplication& operator=(const MprpcApplication&&) = delete;
    static MprpcApplication& Getinstance();
    static void init(int argc, char** argv);
};
