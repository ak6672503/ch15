// TCPClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")


int main()
{
	//加载套接字
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return -1;
	}

	//创建用于监听的套接字
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv; //创建地址结构体变量
	inet_pton(AF_INET, "127.0.0.1", &addrSrv.sin_addr);//把要发到服务端的IP地址转变为二进制格式 复制给地质结构体变量
	addrSrv.sin_family = AF_INET; //因为addrsrv要表示一个IP地址，所以这个值只能是这个
	addrSrv.sin_port = htons(6000);//设定端口

	//向服务器发出连接请求
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//接收数据
	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("%s\n", recvBuf);
	//发送数据
	send(sockClient, "this is list", strlen("this is list") + 1, 0);

	//关闭套接字
	closesocket(sockClient);
	WSACleanup();
	system("PAUSE");
	return 0;





}

