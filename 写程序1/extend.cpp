#include"extend.h"
void serve() {
	//1确定协议版本信息
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	std::cout<<"确认协议版本信息成功！"<<std::endl;
	//2创建socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cout << "创建socket失败！" << std::endl;
		WSACleanup();
		return;
	}
	std::cout << "创建socket成功！" << std::endl;


	//3确定服务器协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//IPv4
	addr.sin_port = htons(8080);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.1");
	//4绑定
	bind(sock, (SOCKADDR*)&addr, sizeof(addr));
	//5监听
	listen(sock, 5);
	std::cout << "监听成功！" << std::endl;
	//6接受连接
	SOCKADDR_IN clientAddr;
	int len = sizeof(clientAddr);
	SOCKET client = accept(sock, (SOCKADDR*)&clientAddr, &len);
	if (client == INVALID_SOCKET) {
		std::cout << "接受连接失败！" << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	
	system("cls");
	std::cout << "接受连接成功！" << std::endl;
	std::cout << "微博推送界面：" << std::endl;
	//7接收数据
	char recvBuf[1024];
	while (true) {
		int recvLen = recv(client, recvBuf, 1024, 0);
		if (recvLen > 0) {
			recvBuf[recvLen] = '\0';//添加结束符
			printf("您更新了一条推送：%s\n", recvBuf);
		}
	}
	//8发送数据
	char sendBuf[1024];
	sprintf_s(sendBuf, "Hello, %s", recvBuf);
	send(client, sendBuf, strlen(sendBuf), 0);
	//9关闭连接
	closesocket(client);
	closesocket(sock);
	WSACleanup();

	std::cout<<"服务器已关闭！"<<std::endl;

}






