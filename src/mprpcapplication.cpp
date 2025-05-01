#include "mprpcapplication.h"

MprpcApplication::MprpcApplication() {}

MprpcApplication& MprpcApplication::Getinstance()
{
    static MprpcApplication instance;
    return instance;
}
void MprpcApplication::init(int argc, char** argv)
{
    
}