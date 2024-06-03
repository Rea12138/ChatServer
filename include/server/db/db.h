#ifndef MYSQL_H
#define MYSQL_H

#include <mysql/mysql.h>
#include <string>
#include <muduo/base/Logging.h>
using namespace std;
using namespace muduo;

class MySQL 
{
public:
    // 初始化数据库连接
    MySQL();
    // 释放数据库连接数据
    ~MySQL();
    // 连接数据库
    bool connect();
    // 更新操作
    bool update(string sql);
    // 查询操作
    MYSQL_RES* query(string sql);
    // 返回MYSQL指针
    MYSQL* getConnection();
private:
    MYSQL *_conn;
};

#endif