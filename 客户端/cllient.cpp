#include<iostream>
#include<Windows.h>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")

int main() {
	SetConsoleTitle(L"�ͻ���");
	//1ȷ��Э��汾��Ϣ
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	std::cout << "ȷ��Э��汾��Ϣ�ɹ���" << std::endl;
	//2����socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cout << "����socketʧ�ܣ�" << std::endl;
		WSACleanup();
		return -1;
	}
	std::cout << "����socket�ɹ���" << std::endl;


	//3ȷ��������Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//IPv4
	addr.sin_port = htons(8080);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.1");
//4 ���ӷ�������
connect(sock, (SOCKADDR*)&addr, sizeof(addr));
std::cout << "���ӷ������ɹ���" << std::endl;
//5 ͨѶ �����û����룬�����͸�������
char input[1024];
while (true) {
	std::cout << "������Ҫ���͵���Ϣ��";
	std::cin.getline(input, 1024);
	send(sock, input, strlen(input), 0);
}

	//9�ر�����
	closesocket(sock);
	WSACleanup();

	std::cout << "�ͻ����ѹرգ�" << std::endl;

}






