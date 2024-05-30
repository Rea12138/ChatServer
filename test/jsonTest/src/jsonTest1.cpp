#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <map>
#include <string>
using namespace std;

string func1()
{
    json js;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg_type"] = 2;
    js["msg"] = "hello, what are you doing now?";

    // cout << js << endl;

    // string sendBuf = js.dump();
    // cout << sendBuf.c_str() << endl;
    return js.dump();
}

string func2()
{
    json js;
    // 添加数组
    js["id"] = {1, 2, 3, 4, 5};
    // 添加key-value
    js["name"] = "zhang san";
    // 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";

    // 上面等同于下面这句一次性添加数组对象(会覆盖上面两句，键是不会重复的)
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello china"}};

    // cout << js << endl;
    return js.dump();
}

string func3()
{
    json js;

    // 序列化vector容器
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(5);

    js["list"] = v;

    // 序列化map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});

    js["path"] = m;
    
    // cout << js << endl;
    return js.dump();
}

int main()
{
    // string sendbuf = func1();
    // json jsonbuf = json::parse(sendbuf);
    // cout << jsonbuf["from"] << endl;
    // cout << jsonbuf["to"] << endl;
    // cout << jsonbuf["msg_type"] << endl;
    // cout << jsonbuf["msg"] << endl;

    // string sendbuf = func2();
    // json jsonbuf = json::parse(sendbuf);

    // auto arr = jsonbuf["id"];
    // cout << arr << endl;
    // cout << arr[2] << endl;

    // cout << jsonbuf["name"] << endl;

    // json jsonmsg = jsonbuf["msg"];
    // cout << jsonmsg["zhang san"] << endl;
    // cout << jsonmsg["liu shuo"] << endl;

    string sendbuf = func3();
    json jsonbuf = json::parse(sendbuf);

    
    vector<int> vec = jsonbuf["list"];
    for (int &i : vec) {
        cout << i << " ";
    }
    cout << endl;

    map<int, string> mymap = jsonbuf["path"];
    for( auto& m : mymap) {
        cout << m.first << " " << m.second << endl;
    }
    return 0;
}