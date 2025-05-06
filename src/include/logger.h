#pragma once 
#include <string>
#include <mutex>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <condition_variable>
#include <thread>
#include <queue>
#include <iostream>
#include <ctime>
class Logger {
    
private:
    void LogThreadFunc();//日志线程函数
    std::queue<std::string> _msgQueue;//消息队列
    std::mutex _mutex;//互斥锁
    std::condition_variable _cond;//条件变量
    std::thread _logThread;//日志线程
    bool stop ;//停止标志
public:

    Logger();
    static Logger& GetInstance();
    Logger(const Logger&) = delete; 
    Logger& operator=(const Logger&) = delete; 
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    ~Logger();
    void Error_Log(std::string msg);//错误日志
    void Info_Log(std::string msg);//信息日志
};