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


	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN addrSrv; //创建地址结构体变量
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//允许套接字向任何分配给本地机器的IP地址发送或接受收据
	addrSrv.sin_family = AF_INET;//TCP\ip协议的套接字，必须设置为AF_INET
	addrSrv.sin_port = htons(6000); //将端口设定为6000

	//绑定套接字
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[200];
	char str[INET_ADDRSTRLEN];
	SOCKADDR_IN  addrClient;
	int len = sizeof(SOCKADDR);

	while (1) {
	//等待并接受数据
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
		if ('q' == recvBuf[0]) {
			sendto(sockSrv, "q", strlen("q" + 1), 0, (SOCKADDR*)&addrClient, len);
			printf("chat end!\n");
			break;
		}
		sprintf_s(tempBuf, 200, "%s say: %s",
			inet_ntop(AF_INET, &addrClient.sin_addr, str, sizeof(str)), recvBuf);

		printf("%s\n", tempBuf);

		//发送数据
		printf("please input data:\n");
		gets_s(sendBuf);
		sendto(sockSrv, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrClient, len);
	}
	//关闭套接字
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}
