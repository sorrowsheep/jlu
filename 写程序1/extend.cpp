#include"extend.h"
void serve() {
	//1ȷ��Э��汾��Ϣ
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	std::cout<<"ȷ��Э��汾��Ϣ�ɹ���"<<std::endl;
	//2����socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cout << "����socketʧ�ܣ�" << std::endl;
		WSACleanup();
		return;
	}
	std::cout << "����socket�ɹ���" << std::endl;


	//3ȷ��������Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;//IPv4
	addr.sin_port = htons(8080);
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.1");
	//4��
	bind(sock, (SOCKADDR*)&addr, sizeof(addr));
	//5����
	listen(sock, 5);
	std::cout << "�����ɹ���" << std::endl;
	//6��������
	SOCKADDR_IN clientAddr;
	int len = sizeof(clientAddr);
	SOCKET client = accept(sock, (SOCKADDR*)&clientAddr, &len);
	if (client == INVALID_SOCKET) {
		std::cout << "��������ʧ�ܣ�" << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	
	system("cls");
	std::cout << "�������ӳɹ���" << std::endl;
	std::cout << "΢�����ͽ��棺" << std::endl;
	//7��������
	char recvBuf[1024];
	while (true) {
		int recvLen = recv(client, recvBuf, 1024, 0);
		if (recvLen > 0) {
			recvBuf[recvLen] = '\0';//��ӽ�����
			printf("��������һ�����ͣ�%s\n", recvBuf);
		}
	}
	//8��������
	char sendBuf[1024];
	sprintf_s(sendBuf, "Hello, %s", recvBuf);
	send(client, sendBuf, strlen(sendBuf), 0);
	//9�ر�����
	closesocket(client);
	closesocket(sock);
	WSACleanup();

	std::cout<<"�������ѹرգ�"<<std::endl;

}






