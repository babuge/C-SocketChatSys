// socket_client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable:4996)

char * s_gets(char*, int);

int main()
{
    SetConsoleTitle(L"client");
    // 定义长度变量
    int send_len = 0;
    int recv_len = 0;
    // 定义发送缓冲区和接收缓冲区
    char send_buf[100];
    char recv_buf[100];
    // 定义套接字
    SOCKET s_send;
    // 定义服务器地址
    SOCKADDR_IN server_addr;
    // 初始化套接字库
    WORD w_req;
    WSADATA wsa_data;
    int err;
    w_req = MAKEWORD(2, 2);
    err = WSAStartup(w_req, &wsa_data);
    if (err != 0)
    {
        printf("初始化套接字库失败！\n");
        return 0;
    }
    // 检测版本号
    if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2)
    {
        printf("套接字库版本号不符！\n");
        WSACleanup();
        return 0;
    }
    char addr[20];
    int port = 0;
    printf("请输入server ip地址：（不输入直接回车）\n");
    if (s_gets(addr, 20) == NULL || addr[0] == '\0')
    {
        strcpy(addr, "127.0.0.1");
    }
    printf("请输入server 端口号4000~9000：（输入0，默认8888）\n");
    scanf("%d", &port);
    while (getchar() != '\n') {
        continue;
    }
    if (port < 4000 || port > 9000) {
        port = 8888;
    }
    // 设置服务器地址信息
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.S_un.S_addr = inet_addr(addr);
    server_addr.sin_port = htons(port);
    // 创建套接字
    s_send = socket(AF_INET, SOCK_STREAM, 0);
    // 连接请求
    if (connect(s_send, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        printf("服务器连接失败！\n");
        WSACleanup();
        return 0;
    }
    printf("与服务器连接成功！\n");
    // 发送、接收数据
    while (1)
    {
        printf("输入发送消息：\n");
        if (s_gets(send_buf, 100) == NULL || send_buf[0] == '\0') 
        {
            // continue;
        }
        send_len = send(s_send, send_buf, 100, 0);
        if (send_len < 0)
        {
            printf("发送失败！\n");
            break;
        }
        recv_len = recv(s_send, recv_buf, 100, 0);
        if (recv_len < 0)
        {
            printf("接收失败！\n");
            break;
        }
        else 
        {
            printf("服务端消息：%s\n", recv_buf);
        }
    }
    // 关闭套接字
    closesocket(s_send);
    // 释放套接字库资源
    WSACleanup();
    return 0;
}

char * s_gets(char* st, int n)
{
    char* ret_val;
    char* find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');
        if (find)
        {
            *find = '\0';
        }
        else
        {
            while (getchar() != '\n')
            {
                continue;
            }
        }
    }
    return ret_val;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
