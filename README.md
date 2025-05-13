## 分布式网络通信框架

### 项目介绍

开发了一个基于C++高性能RPC分布式网络通信框架，支持将单体架构的本地方法调用，重构为基于TCP的远程调用，支持同一台机器的不同进程和不同机器之间的服务调用。适用于将单体架构转为分布式微服务架构。

### 技术栈：

#### **1、RPC**

RPC( Remote Procedure  Call Protocol ) ，是用于实现远程过程调用的通信协议，允许程序调用远程服务器上的函数，就像调用本地函数一样的技术。

#### **2、Protobuf**

**Protobuf（Protocol Buffers）** 是一种高效的序列化协议，由 Google 开发，适用于跨语言、跨平台数据交换。序列化后是二进制数据，它比 JSON 和 XML 更高效，占用更少的带宽。

#### 3、Zookeeper

**Zookeeper** : 是一个 分布式协调服务，用于管理分布式系统中的元数据、服务注册发现、集群管理等任务。

#### 4、高性能网络通信( Muduo )

基于 **Muduo** 网络库，采用 Reactor 模型 实现高并发异步通信。是C++ 服务器开发的常用库，适合构建高性能、高并发的网络服务。

#### 5、异步日志

异步日志是一种日志处理技术，通过将日志写入操作从主线程分离，避免因 I/O 操作阻塞影响程序性能，特别适用于高并发、高吞吐量的应用场景。

#### 6、.conf 配置文件的读取

`.conf` 配置文件是一种文本格式的配置文件，通常用于存储程序的配置信息，如参数、路径、日志级别等。常见于 Linux 服务、应用程序、数据库等。

### 开发环境

##### ubuntu20.04。

##### Muduo网络库的安装

```cpp
# 安装 Boost 库（Muduo 依赖 Boost）
sudo apt install -y libboost-all-dev

# 下载并编译 Muduo
git clone https://github.com/chenshuo/muduo.git
cd muduo
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install
```

##### Protobuf安装

```cpp
# 安装构建工具和依赖项。
apt-get install autoconf automake libtool curl make g++ unzip  
git clone -b v21.12 https://github.com/protocolbuffers/protobuf.git
cd protobuf 
# 初始化并更新 Git 子模块（Submodule），确保所有子模块正确拉取到项目中    
git submodule update --init --recursive 
mkdir build && cd build
# 配置 Protobuf 编译选项，让 Protobuf 在构建时正确使用 Abseil（Absl）库，并禁用测试，以加快编译速度
cmake -Dprotobuf_BUILD_TESTS=OFF .. 
make -j$(nproc)  # -j$(nproc) 选项可以大幅提升编译速度,如果中途出现error, 那就使用make不带任何参数
sudo make install 
sudo ldconfig  # 刷新动态库
protoc --version  # 验证安装
```

##### 注意

make构建项目的时候出现  

**undefined reference to `absl::lts_20250127::log_internal::LogMessage::operator<<(std::basic_string_view<char, std::char_traits<char> >)'**

这个错误表明 **Protobuf 编译时未正确链接 Abseil（absl）库**，导致 `undefined reference`（未定义引用）错误。

安装 `Abseil` 库

```cpp
git clone https://github.com/abseil/abseil-cpp.git
cd abseil-cpp
git checkout lts_2023_08_02
mkdir build && cd build
cmake -DCMAKE_CXX_STANDARD=17 -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..
make -j$(nproc)
sudo make install
```

然后 重新编译 Protobuf。

##### Zookeeper 安装

```cpp
wget https://dlcdn.apache.org/zookeeper/zookeeper-3.8.4/apache-zookeeper-3.8.4.tar.gz   # 源码下载
tar -zxvf apache-zookeeper-3.8.4.tar.gz
cd apache-zookeeper-3.8.4
cd conf/
cp zoo_sample.cfg zoo.cfg
cd ..
# 编译
sudo apt install maven
mvn clean install -DskipTests
cd bin/
# 启动
./zkServer.sh  start
```

**注意: **ZooKeeper 需要 Java 开发环境，因为它是用 Java 编写的，并且运行时依赖 Java 虚拟机（JVM）。要成功运行 ZooKeeper，你需要正确安装 Java 开发工具（JDK）。

```
sudo apt update
sudo apt install -y openjdk-11-jdk
# 检查是否成功
java -version

# 设置 JAVA_HOME
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH

# 让 JAVA_HOME 永久生效
echo 'export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64' >> ~/.bashrc
echo 'export PATH=$JAVA_HOME/bin:$PATH' >> ~/.bashrc
source ~/.bashrc
```

##### Zookeeper 编译C开发接口

```
cd apache-zookeeper-3.8.4/zookeeper-client/zookeeper-client-c
sudo ./configure
sudo make
sudo make install
```

##### 判断 ZooKeeper C API 编译是否成功

```cpp
# 1. 确保库文件 libzookeeper_mt.so 存在
ls -l /usr/local/zookeeper-c/lib    # 有输出
```

##### 测试用例

```cpp
#include <stdio.h>
#include <zookeeper/zookeeper.h>

void watcher(zhandle_t *zh, int type, int state, const char *path, void *watcherCtx) {
    printf("Watcher event triggered: %s\n", path);
}

int main() {
    const char *host = "127.0.0.1:2181";
    zhandle_t *zh = zookeeper_init(host, watcher, 30000, 0, NULL, 0);

    if (zh == NULL) {
        printf("Failed to connect to ZooKeeper!\n");
        return -1;
    }

    printf("Connected to ZooKeeper!\n");

    zookeeper_close(zh);
    return 0;
}
```

##### 编译

```cpp
gcc test_zk.c -o test_zk -I/usr/local/zookeeper-c/include -L/usr/local/zookeeper-c/lib -lzookeeper_mt
```

#### Protobuf

##### 1、优点

* 高效：二进制格式，比 JSON / XML 体积更小、解析更快。
* 跨语言：支持 C++、Python、Go、Java、Rust 等。
* 可扩展：向后兼容，允许新增字段而不影响旧版本。
* 自动生成代码：`protoc` 编译 `.proto` 文件，生成序列化 / 反序列化代码。

##### **2、 .proto**配置文件编写，举例。

```cpp
syntax = "proto3";

package fixbug;
option cc_generic_services = true;

message LoginRequest {
	string name = 1;
	string pwd  = 2;
}

message RegRequest {
	string name = 1;
	string pwd  = 2;
	int32 age  = 3;
	enum SEX {
		MAN = 0;
		WOMAN = 1;
	}
	SEX sex = 4;
	string phone = 5;
}

message Response {
	int32 errorno = 1;
	string errormsg = 2;
	bool result = 3;
}

// 定义RPC服务接口类和服务方法
service UserServiceRpc{
	rpc login(LoginRequest) returns (Response);
	rpc reg(RegRequest) returns (Response);
}
```

##### 3、如何编译**.proto**文件

```cpp
# ./生成文件输出路径在当前目录下
protoc -I=./ --cpp_out=./  bike.proto
```

##### 4、如何使用?

```cpp
#include <iostream>
#include <string>

#include "test.pb.h"

int main() {

    // 创建 Protobuf 对象
    fixbug::LoginRequest req;
    req.set_name("wuxf");
    req.set_pwd("23456");

    // 序列化
    int size = req.ByteSize();
    char str[size] = {0};
    if ( req.SerializeToArray(str, sizeof(str)) )
    {
        std::cout << str << std::endl;
    }


    // 反序列化
    fixbug::LoginRequest req1;

    if (req1.ParseFromArray(str, size))
    { // 直接用 string 反序列化
        std::cout << "Deserialized data:" << std::endl;
        std::cout << "Name: " << req1.name() << std::endl;
        std::cout << "Password: " << req1.pwd() << std::endl;
    }

    return 0;
}

```

**5、编译**

```cpp
g++ --std=c++11 example.cc bike.pb.cc -o example.exe  -lprotobuf
```

#### Zookeeper 分布式协调服务

它广泛用于 **分布式系统**。本项目只用到  服务注册 & 发现。

* 分布式协调:   解决 **多个节点之间的数据一致性问题**。
* 服务注册 & 发现:  记录 **服务的 IP:PORT**，客户端可动态发现。
* 分布式锁 : 保障多个节点 **不会同时访问共享资源**。
* 集群 Leader 选举 :  在 **Master-Slave 结构** 下，选举 Leader。
* 分布式通知 & Watch 机制 :  监听数据变化，**自动通知** 客户端

##### ZooKeeper 的数据模型------znode节点

ZooKeeper 采用 层级结构，类似于 Linux 文件系统：

![zookeeper数据存储格式](img\zookeeper数据存储格式.png)

##### 常用的一些操作

```cpp
# 创建 ZNode
create /myapp "Hello ZooKeeper"

# 读取 ZNode 数据
get /myapp
    
# 更新 ZNode 数据
set /myapp "Updated Data"

# 删除 ZNode
delete /myapp

# 列出myapp下的节点
ls /myapp
```

##### 参考连接

[ZooKeeper原理及介绍](https://www.cnblogs.com/xinyonghu/p/11031729.html)

#### 什么是集群?

**集群: **由 多台服务器（或计算机） 组成的一个整体，每一台服务器独立运行一个工程的所有模块。

#### 什么是分布式? 

**分布式: **一个工程拆分多个模块，每个模块独立运行在不同的服务器上，所有服务器协同工作提供完整的服务。每一台服务器称作分布式的一个节点，根据节点的并发要求，对一个节点可以再做节点模块集群部署。

### rpc通信原理

![通信原理](img\通信原理.png)

**User-Stub、Server-Stub: **设计rpc方法参数的打包盒解析，也就是数据的序列化和反序列化 ， 使用的是 protobuf 来完成。

**RPC-RunTime:**网络部分，包括寻找 rpc 服务主机，发起rpc调用请求和响应rpc调用结果，使用muduo网络库。

### 程序运行流程 ( 时序图 )

![项目运行流程](img\项目运行流程.png)

### 框架服务端设计类图

![框架服务端设计类图](img\框架服务端设计类图.png)

**UserService : ** RPC服务发布类( rpc服务提供者 ) , 原本提供本地服务（如`Login`和`Register`），现在封装成RPC服务，供远程调用。

**RpcProvider : ** 它是RPC框架中的服务提供方（服务端），负责将本地服务方法发布到网络，让远程客户端通过网络调用本地方法 , 包括请求处理及响应。

**MprpcApplication : **框架初始化类，用于初始化整个RPC系统环境（加载配置文件）, 提供全局唯一的配置访问入口。

**MprpcConfig : **配置管理类，负责加载并解析RPC服务的配置文件（如服务器IP、端口、Zookeeper地址等），提供配置查询功能。

**Logger :**  异步单例日志类。

**MprpcController: ** 负责在RPC调用过程中，记录和报告RPC调用过程的状态和错误信息。

**ZkClient : **用于管理与Zookeeper的连接、节点创建、节点数据查询 , 用于服务注册、服务发现。

### 框架使用端设计类图

![框架使用端设计类图](img\框架使用端设计类图.png)

****

**MprpcChannel: **作为RPC客户端的核心通信模块，负责将RPC调用请求序列化后通过网络发送给RPC服务端，并接收、反序列化响应结果。