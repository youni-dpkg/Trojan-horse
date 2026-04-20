#include<stdio.h>
#include<winsock2.h>						//Windows Socket API 2.0
#include<ws2tcpip.h>						//tcp/ip扩展内容
#pragma comment(lib,"ws2_32.lib")			//连接Winsock库

SOCKET client_strl(const char* ip, int port) {
	WSADATA wsaData;						//存储winsock信息
	SOCKET client_socket = INVALID_SOCKET;	//客户端初始无效值
	struct sockaddr_in server_addr;			//服务器地质结构

	/*初始化Winsock*/
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);		//WSAStart初始化SOCKET，MAKEWORD：请求WINSOCK2.2版本库
	if (iResult != 0) {
		printf("WSAStartup failed:%d\n", iResult);
		return INVALID_SOCKET;								//失败返回INVALID_SOCKET，表示失败
	}

	/*创建SOCK*/
	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client_socket == INVALID_SOCKET) {
		printf("socket faild:%d\n", WSAGetLastError());
		WSACleanup();
		return INVALID_SOCKET;
	}

	/*设置是服务器地址*/
	server_addr.sin_family = AF_INET;							//设置IPv4家族
	server_addr.sin_port = htons(port);							//设置端口
	server_addr.sin_addr.s_addr = inet_addr(ip);				//设置IP地址，inet_addr函数将转成网络数据

	/*建立连接*/
	iResult = connect(client_socket,(struct sockaddr*)&server_addr, sizeof(server_addr));
	if (iResult == SOCKET_ERROR) {								//判断是否连接失败
		printf("Connect fail ： %d\n", WSAGetLastError());		
		closesocket(client_socket);								//失败关闭套接字
		WSACleanup();											//
		return INVALID_SOCKET;
	}
	return client_socket;
}

int main() {
	SOCKET client_socket = client_strl("192.168.11.131", 3333);
	/*先理解代码吧*/
	return 0;
}