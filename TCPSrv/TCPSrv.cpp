// TCPSrv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include<WinSock2.h>
#include<ws2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")



int main()
{
	//加载套接字库
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
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv; //创建地址结构体变量
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//允许套接字向任何分配给本地机器的IP地址发送或接受收据
	addrSrv.sin_family = AF_INET;//TCP\ip协议的套接字，必须设置为AF_INET
	addrSrv.sin_port = htons(6000); //将端口设定为6000

	//绑定套接字
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//将套接字设为监听模式，准备接受客户请求
	listen(sockSrv, 5);

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while (1) {
	//等待客户请求的到来
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		char sendBuf[100]; //存储要接收的数据和要发出去的数据
		char str[INET_ADDRSTRLEN]; //存储发过来的对方IP信息
		sprintf_s(sendBuf, 100, "welcome %s to www.baidu.com", inet_ntop(AF_INET, &addrClient.sin_addr, str, sizeof(str)));
		//设置要发出去的数据
		
		//发送数据
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);

		char recvBuf[100];

		//接收数据
		recv(sockConn, recvBuf, 100, 0);
		//打印接收到的数据
		printf("%s\n", recvBuf);
		//关闭套接字
		closesocket(sockConn);
	}
	return 0;
}
