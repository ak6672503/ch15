#include<WinSock2.h>
#include<WS2tcpip.h>
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

	//创建套接字
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	inet_pton(AF_INET, "127.0.0.1", &addrSrv.sin_addr);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);


	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[200];
	char str[INET_ADDRSTRLEN];
	int len = sizeof(SOCKADDR);

	while (1) {
		printf("please input data:\n");
		gets_s(sendBuf);
		sendto(sockClient, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrSrv, len);

		//等待并接受数据
		recvfrom(sockClient, recvBuf, 100, 0, (SOCKADDR*)&addrSrv, &len);
		if ('q' == recvBuf[0]) {
			sendto(sockClient, "q", strlen("q" + 1), 0, (SOCKADDR*)&addrSrv, len);
			printf("chat end!\n");
			break;
		}
		sprintf_s(tempBuf, 200, "%s say : %s", inet_ntop(AF_INET, &addrSrv.sin_addr, str, sizeof(str)), recvBuf);
		printf("%s\n", tempBuf);
	}
	//关闭套接字
	closesocket(sockClient);
	WSACleanup();
	return 0;




}
