#include <functional>
#include <iostream>
#include <string>
using namespace std;
using namespace placeholders;

#include "chatservice.hpp"
#include "chatserver.hpp"
#include "json.hpp"
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop* loop,
            const InetAddress& listenAddr,
            const string& nameArg)
    :_server(loop, listenAddr, nameArg), _loop(loop)
{
    // 设置客户端连接与断开的回调函数
    _server.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));

    // 设置读写回调函数
    _server.setMessageCallback(bind(&ChatServer::onMessage, this, _1, _2, _3));
    
    // 设置线程数量
    _server.setThreadNum(2);
}

void ChatServer::start()
{
    _server.start();
}

void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    // 如果断开连接，则释放套接字资源
    if (!conn->connected())
    {
        conn->shutdown();
    }
    else 
    {
        cout << "connected" << endl;
    }
}

void ChatServer::onMessage(const TcpConnectionPtr& conn,
                            Buffer* buffer,
                            Timestamp time)
{
    cout << "In onMessage" << endl;
    string buf = buffer->retrieveAllAsString();
    json js = json::parse(buf);
    // 根据js中的["msg_type"]，执行不同的handler（conn，js，time），实现网络模块和业务模块的解耦
    auto msgHandler = ChatService::getInstance()->getHandler(js["msg_type"].get<int>());
    msgHandler(conn, js, time);
}
