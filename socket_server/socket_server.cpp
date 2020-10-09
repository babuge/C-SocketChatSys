// socket_first.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <winsock.h>
#include <time.h>
#include <string.h>
#include <string>

#include "time_format.h"


#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable:4996)

char * s_gets(char*, int);

int main()
{
	SetConsoleTitle(L"server");
	// 定义长度
	int send_len = 0;
	int recv_len = 0;
	int len = 0;

	// 定义发送缓冲区和接收缓冲区
	char send_buf[100];
	char recv_buf[100];
	// 定义服务器套接字、接收请求套接字
	SOCKET s_server;
	SOCKET s_accept;
	// 定义服务器地址、客户端地址
	SOCKADDR_IN server_addr;
	SOCKADDR_IN client_addr;
	// 初始化套接字库
	WORD w_req;
	WSADATA wsa_data;
	int err;
	w_req = MAKEWORD(2, 2);
	err = WSAStartup(w_req, &wsa_data);
	if (err != 0)
	{
		printf("初始化套接字库失败!\n");
		return 0;
	}
	// 检测版本号
	if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2)
	{
		printf("套接字版本号不符！\n");
		WSACleanup();
		return 0;
	}
	int port = 0;
	printf("请输入端口号4000~9000：（输入0，默认8888）\n");
	scanf("%d", &port);
	while (getchar() != '\n') {
		continue;
	}
	if (port <4000 || port > 9000) {
		port = 8888;
	}
	// 填充服务端地址信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	// 创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	// 创建套接字绑定到本地地址
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("套接字绑定失败！\n");
		WSACleanup();
		return 0;
	}

	// 设置套接字为监听状态
	if (listen(s_server, 5) < 0)
	{
		printf("设置套接字监听失败！\n");
		WSACleanup();
		return 0;
	}
	printf("服务器正在监听连接，请稍后。。。\n");
	// 接收连接请求
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR*)&client_addr, &len);
	if (s_accept == SOCKET_ERROR)
	{
		printf("接收连接失败！\n");
		WSACleanup();
		return 0;
	}
	printf("连接建立...准备接收数据\n");
	// 接收，发送数据
	while (1)
	{
		recv_len = recv(s_accept, recv_buf, 100, 0);
		if (recv_len < 0)
		{
			printf("接收失败！\n");
			break;
		}
		else
		{
			printf("客户端信息：%s\n", recv_buf);
		}
		if(strcmp(recv_buf,"getTime") == 0)
		{
			SYSTEMTIME sysTime;
			GetLocalTime(&sysTime);
			SystimeToString(&sysTime, send_buf);
			printf("回复消息-本地时间：%s\n", send_buf);
		}
		else
		{
			printf("请输入回复消息：\n");
			if (s_gets(send_buf, 100) == NULL || send_buf[0] == '\n')
			{
				// continue;
			}
		}
		
		send_len = send(s_accept, send_buf, 100, 0);
		if (send_len < 0)
		{
			printf("发送失败！\n");
			break;
		}
	}
	// 关闭套接字连接
	closesocket(s_accept);
	closesocket(s_server);
	// 释放动态库资源
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
