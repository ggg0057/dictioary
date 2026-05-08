#include "client.hpp"
#include <stdexcept> //异常处理类

// 构造函数的定义
DictClient::DictClient(const string &ip, int port) : sockfd_(-1), is_logged_in_(false)
{

    if (!connectToServer(ip, port))
    {
        throw runtime_error("connect to server error");
    }
}

// 析构函数
DictClient::~DictClient()
{

    if (sockfd_ >= 0)
    {
        doQuit();
        close(sockfd_);
    }
}


bool DictClient::connectToServer(const string &ip, int port)
{

    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ < 0)
    {
        perror("socket error");
        return false;
    }


    int opt = 1;
    if (setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt error");
        return false;
    }

    // 连接服务器
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(ip.c_str());

    // 连接服务器
    if (connect(sockfd_, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("connect error");
        return false;
    }

    return true;
}
