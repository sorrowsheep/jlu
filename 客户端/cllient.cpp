#include<iostream>
#include<Windows.h>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")

int main() {
	SetConsoleTitle(L"客户端");
	//1确定协议版本信息
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	std::cout << "确认协议版本信息成功！" << std::endl;
	//2创建socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cout << "创建socket失败！" << std::endl;
		WSACleanup();
		return -1;
	}
	std::cout << "创建socket成功！" << std::endl;


	//3确定服务器协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//IPv4
	addr.sin_port = htons(8080);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.1");
//4 连接服务器、
connect(sock, (SOCKADDR*)&addr, sizeof(addr));
std::cout << "连接服务器成功！" << std::endl;
//5 通讯 接受用户输入，并发送给服务器
char input[1024];
while (true) {
	std::cout << "请输入要发送的消息：";
	std::cin.getline(input, 1024);
	send(sock, input, strlen(input), 0);
}

	//9关闭连接
	closesocket(sock);
	WSACleanup();

	std::cout << "客户端已关闭！" << std::endl;

}






