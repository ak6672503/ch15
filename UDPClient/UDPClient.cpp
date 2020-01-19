
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

	//创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	inet_pton(AF_INET, "127.0.0.1", &addrSrv.sin_addr);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	//发送数据
	sendto(sockClient, "Hello", strlen("Hello") + 1, 0,
		(SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	//关闭套接字
	closesocket(sockClient);
	system("PAUSE");

	WSACleanup();

}
