#include "chatservice.hpp"

#include <muduo/base/Logging.h>
using namespace muduo;
using namespace placeholders;

// 获取单例的接口函数
ChatService* ChatService::getInstance()
{
    static ChatService instance;
    return &instance;
}

// 注册不同消息的回调函数
ChatService::ChatService()
{
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3)});
    _msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3)});

}

MsgHandler ChatService::getHandler(int msgid)
{
    auto it = _msgHandlerMap.find(msgid);
    if (it == _msgHandlerMap.end())
    {
        // 返回一个默认hanlder，空操作
        return [msgid](const TcpConnectionPtr& conn, json& js, Timestamp time) {
            LOG_ERROR << "can not find " << msgid << " handler!";            
        };
    }
    else
    {
        return _msgHandlerMap[msgid];
    }
    
}


// 登录业务函数
void ChatService::login(const TcpConnectionPtr& conn, json& js, Timestamp time)
{
    LOG_INFO << "login~";
}
// 注册业务函数
void ChatService::reg(const TcpConnectionPtr& conn, json& js, Timestamp time)
{
    LOG_INFO << "reg~";
}
