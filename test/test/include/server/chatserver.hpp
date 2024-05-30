#pragma once
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

// 聊天服务器的主类
class ChatServer 
{
public:
    // 初始化服务器类对象
    ChatServer(EventLoop* loop,
            const InetAddress& listenAddr,
            const string& nameArg);
    
    // 启动服务
    void start();
    
    // 上报客户端连接与断开事件的回调函数
    void onConnection(const TcpConnectionPtr&);

    // 上报客户端读写事件的回调函数
    void onMessage(const TcpConnectionPtr&,
                            Buffer*,
                            Timestamp);
private:
    TcpServer _server;  // 使用muduo网络库，实现服务器相关功能的类对象
    EventLoop *_loop;   // 指向事件循环的指针
};