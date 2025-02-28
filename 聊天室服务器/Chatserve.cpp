#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <winsock.h>
#include <mutex>
#pragma comment(lib,"ws2_32.lib")
#define NUM 1024
#define MAX_BUFFER_SIZE 512

SOCKET client[NUM];
int clientNum = 0;
std::mutex clientMutex;

void BroadcastMessage(const char* message, int length) {
    std::lock_guard<std::mutex> lock(clientMutex);
    for (int i = 0; i < clientNum; i++) {
        send(client[i], message, length, 0);
    }
}

void tongxin(int idx) {
    char recvBuf[MAX_BUFFER_SIZE];
    char temp[1024];
    while (true) {
        int r = recv(client[idx], recvBuf, MAX_BUFFER_SIZE - 1, 0);
        if (r > 0) {
            recvBuf[r] = '\0'; // ��ӽ�����
            printf("���յ����ݣ�%s\n", recvBuf);
            if (strcmp(recvBuf, "exit") == 0) {
                break; // �����˳��߼�
            }
            sprintf_s(temp, "%d˵��%s", idx, recvBuf);
            BroadcastMessage(temp, strlen(temp));
        }
        else if (r == 0) {
            printf("�����ѹر�\n");
            break;
        }
        else {
            printf("���մ��󣬴�����룺%d\n", WSAGetLastError());
            break;
        }
    }
    closesocket(client[idx]);
}

int main() {
    SetConsoleTitle(L"�����ҷ�����");

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    std::cout << "ȷ��Э��汾��Ϣ�ɹ���" << std::endl;

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "����socketʧ�ܣ�������룺" << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }
    std::cout << "����socket�ɹ���" << std::endl;

    SOCKADDR_IN addr = { 0 };
    addr.sin_family = AF_INET; // IPv4
    addr.sin_port = htons(10000);
    addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.1");

    bind(sock, (SOCKADDR*)&addr, sizeof(addr));
    listen(sock, 5);
    std::cout << "�����ɹ���" << std::endl;

    for (int i = 0; i < NUM; i++) {
        SOCKADDR_IN clientAddr;
        int len = sizeof(clientAddr);
        client[i] = accept(sock, (SOCKADDR*)&clientAddr, &len);
        if (client[i] == INVALID_SOCKET) {
            std::cerr << "��������ʧ�ܣ�������룺" << WSAGetLastError() << std::endl;
            closesocket(sock);
            WSACleanup();
            return -1;
        }
        std::cout << "�������ӳɹ���" << std::endl;

        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)tongxin, (LPVOID)i, 0, NULL);
        {
            std::lock_guard<std::mutex> lock(clientMutex);
            clientNum++;
        }
    }

    closesocket(sock);
    WSACleanup();
    std::cout << "�������ѹرգ�" << std::endl;
    return 0;
}
