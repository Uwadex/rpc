#include "logger.h"
void Logger::LogThreadFunc()
{
    while(1)
    {
        std::unique_lock<std::mutex>lock(_mutex);
        _cond.wait(lock,[this](){return (!_msgQueue.empty() || stop);});
        if(_msgQueue.empty() && stop)
        {
            break;
        }
        std::string msg = _msgQueue.front();
        _msgQueue.pop();
        //日志系统只需要一个线程处理日志 只需要防止和其它线程发生队列的数据竞争即可
        lock.unlock();
        //文件名的格式为 年-月—日_log.txt
        std::time_t currentTime = std::time(nullptr);
        // 将时间转换为本地时间结构
        std::tm* localTime = std::localtime(&currentTime);
    
        // 获取年、月、日
        int year = localTime->tm_year + 1900;
        int month = localTime->tm_mon + 1;
        int day = localTime->tm_mday;
        std::string filename = std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day) + "_log.txt";
        //打开文件
        std::ofstream File(filename, std::ios::app);
        if(!File.is_open())
        {
            std::cout << "open file error!" << std::endl;
            return;
        }
        //日志信息格式为 时：分:秒 =>+msg
        std::time_t now = std::time(nullptr);
        std::tm* timeinfo = std::localtime(&now);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
        std::string timeStr(buffer);
        std::string logMsg = timeStr + " => " + msg + "\n";
        File << logMsg;
        File.close();
    }
}
Logger::Logger():stop(false),_logThread(&Logger::LogThreadFunc,this){
}
Logger::~Logger()
{
    
    {
        std::unique_lock<std::mutex>lock(_mutex);
        stop = true;
        _cond.notify_one();
    }
    //如果还有日志没有写入完成 等待所有日志写完
    if(_logThread.joinable())
    {
        _logThread.join();
    }
}
Logger& Logger::GetInstance()
{
    static Logger instance;
    return instance;
}
void Logger::Error_Log(std::string msg)
{
    //加上error前缀
    msg = "error: " + msg;
    //放入任务队列
    std::unique_lock<std::mutex>lock(_mutex);
    _msgQueue.push(msg);
    _cond.notify_one();
}
void Logger::Info_Log(std::string msg)
{
    //加上error前缀
    msg = "info: " + msg;
    //放入任务队列
    std::unique_lock<std::mutex>lock(_mutex);
    _msgQueue.push(msg);
    _cond.notify_one();
}