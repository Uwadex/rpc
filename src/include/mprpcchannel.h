#pragma once
#include <string>
#include <netinet/in.h>
#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include "header.pb.h"
 #include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include "mprpcapplication.h"
#include <arpa/inet.h>
#include <unistd.h>
#include "logger.h"
class MprpcChannel:public google::protobuf::RpcChannel
{
public:
void CallMethod(const google::protobuf::MethodDescriptor* method,
    google::protobuf::RpcController* controller, const google::protobuf::Message* request,
    google::protobuf::Message* response, google::protobuf::Closure* done)override;
};