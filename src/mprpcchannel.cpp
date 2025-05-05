#include "mprpcchannel.h"
//重写RpcChannel的CallMethod方法
void MprpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
    google::protobuf::RpcController* controller, const google::protobuf::Message* request,
    google::protobuf::Message* response, google::protobuf::Closure* done)
    {
        //按照规定格式进行序列化需要发送的字节流
        const google::protobuf::ServiceDescriptor* service = method->service();
        std::string service_name = service->full_name();
        std::string method_name = method->name();
        fixbug::header head;
        head.set_servicename(service_name);
        head.set_methodname(method_name);
        head.set_args_size(request->ByteSizeLong());
        std::string headbuf = head.SerializeAsString();
        std::string argsbuf = request->SerializeAsString();
        char sendbuf[4 + headbuf.size() + argsbuf.size()];
        *((int32_t*)sendbuf) = headbuf.size()+argsbuf.size();
        memmove(sendbuf + 4, headbuf.c_str(), headbuf.size());
        memmove(sendbuf + 4 + headbuf.size(), argsbuf.c_str(), argsbuf.size());
        //进行网络通信
        int client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(client_fd == -1)
        {
            std::cout << "socket error!" << std::endl;
            return;
        }
        //获取config配置项
        std::string ip = MprpcApplication::Getconfig().Load("rpcserverip");
        std::string port = MprpcApplication::Getconfig().Load("rpcserverport");
        struct sockaddr_in server_addr;
        memset(&server_addr,0,sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(std::stoi(port));
        server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
        if(connect(client_fd,(sockaddr*)&server_addr,sizeof(server_addr)) == -1)
        {
            std::cout << "connect error!" << std::endl;
            close(client_fd);
            return;
        }
        if(send(client_fd,sendbuf,sizeof(sendbuf),0) == -1)
        {
            std::cout << "send error!" << std::endl;
            close(client_fd);
            return;
        }
        //接收数据
        char recvbuf[1024] = {0};
        int read_size = recv(client_fd,recvbuf,sizeof(recvbuf),0);
        if(read_size <= 0)
        {
            std::cout << "recv error!" << std::endl;
            close(client_fd);
            return;
        }
        //反序列化
        std::string responsebuf = std::string(recvbuf,read_size);
        if(!response->ParseFromString(responsebuf))
        {
            std::cout << "response parse error!" << std::endl;
            close(client_fd);
            return;
        }
        close(client_fd);
    }   