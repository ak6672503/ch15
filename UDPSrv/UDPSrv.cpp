#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")
#include <iostream>

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


	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN addrSrv; //创建地址结构体变量
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//允许套接字向任何分配给本地机器的IP地址发送或接受收据
	addrSrv.sin_family = AF_INET;//TCP\ip协议的套接字，必须设置为AF_INET
	addrSrv.sin_port = htons(6000); //将端口设定为6000

	//绑定套接字
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	//等待并接收数据
	sockaddr_in addrClient;
	int len = sizeof(SOCKADDR);
	char recvBuf[100];
	recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
	printf("%s\n", recvBuf);
	//关闭套接字
	closesocket(sockSrv);
	WSACleanup();
	return 0;



}

