/*
muduo网络库为用户提供了两个主要的类
TcpServer : 用于编写服务端程序
TcpClient : 用于编写客户端程序

epoll + 线程池 
好处：能够把网络I/O代码和业务代码给分开
                    网络连接与断开      用户的读写事件
*/
#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
#include<iostream>
#include<string>
#include<functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;
/*
基于muduo网络库开发服务程序
1. 组合TCPServer对象
2. 创建EventLoop指针
3. 明确TCPServer需要构造函数需要什么参数，要用来构造TCPServer对象(通过查看TcpServer代码，可以发现并没有默认构造函数，
                                                            所以要构造TcpServer对象必须传入参数，否则无法生成这个对象了)
4. 在当前服务器类的构造函数中，注册处理连接和读写事件的回调函数                                                    
  处理客户端连接和断开的回调
  void setConnectionCallback(const ConnectionCallback& cb)
  { connectionCallback_ = cb; }

  处理读写事件的回调
  void setMessageCallback(const MessageCallback& cb)
  { messageCallback_ = cb; }
5. 设置合适的服务器线程数量，muduo库会自己分配I/O线程和worker线程(一般CPU几核就是几线程)
*/

class ChatServer 
{
public:
    ChatServer(EventLoop* loop,             // 事件循环(epoll)
            const InetAddress& listenAddr,  // IP + Port
            const string& nameArg)          // 服务器名字
            : _server(loop, listenAddr, nameArg),
            _loop(loop)
    {
        // 在回调函数中写自己的业务
        // 给服务器连接和断开设置回调函数
        _server.setConnectionCallback(bind(&ChatServer::onConnection, this, placeholders::_1));
        // 给服务器读写设置回调函数
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
        // 设置线程数量，分配情况是1个I/O线程（处理新用户的连接事件），其他的都是worker（处理读写事件）线程。
        _server.setThreadNum(2);
    }
    // 开启事件循环
    void _start()
    {
        _server.start();
    }
private:
    // 专门处理用户连接的创建和断开的回调函数 epoll listenfd accept 
    void onConnection(const TcpConnectionPtr& conn) {
        // 创建连接时
        if (conn->connected()) {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << ", state: online" << endl;
        }
        // 连接断开时 
        else {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << ", state: offline" << endl;    
            conn->shutdown();    // close(fd);
            // _loop->quit(); 退出epoll，服务结束
        }
    }
    
    // 专门处理用户的读写时间的回调函数
    void onMessage (const TcpConnectionPtr& conn,
                            Buffer* buffer,
                            Timestamp time)
    {
        // echo处理   
        string buf = buffer->retrieveAllAsString();
        cout << "From " << conn->peerAddress().toIpPort() << "recv data " << buf << " time: " << time.toString() << endl;
        conn->send(buf);
    }

    
    // 1.
    muduo::net::TcpServer _server;
    // 2. 可以当成epoll，可以添加事件，有事件会上报进行处理
    muduo::net::EventLoop *_loop;

    
};

int main()
{
    InetAddress addr("127.0.0.1", 6000);
    EventLoop loop;
    ChatServer server(&loop, addr, "ChatServer");  
    server._start();    // listenfd epoll_ctl->epoll
    loop.loop();        // epoll_wait 以阻塞方式等待新用户连接，已连接用户的读写事件等
    return 0;
}