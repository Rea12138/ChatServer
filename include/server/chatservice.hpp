#include <functional>
#include <unordered_map>
#include <muduo/net/TcpConnection.h>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

#include "public.hpp"
#include "json.hpp"
using json = nlohmann::json;

// 消息回调的方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr&, json&, Timestamp)>;


class ChatService
{
public:
    // 获取单例的接口函数
    static ChatService* getInstance();

    // 获取消息对应的Handler
    MsgHandler getHandler(int id);
private:
    // 注册不同消息的回调函数
    ChatService();
    // 登录业务函数
    void login(const TcpConnectionPtr&, json&, Timestamp);
    // 注册业务函数
    void reg(const TcpConnectionPtr&, json&, Timestamp);
    // 存储消息id和其对应业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;

};