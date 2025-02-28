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
            recvBuf[r] = '\0'; // 添加结束符
            printf("接收到数据：%s\n", recvBuf);
            if (strcmp(recvBuf, "exit") == 0) {
                break; // 处理退出逻辑
            }
            sprintf_s(temp, "%d说：%s", idx, recvBuf);
            BroadcastMessage(temp, strlen(temp));
        }
        else if (r == 0) {
            printf("连接已关闭\n");
            break;
        }
        else {
            printf("接收错误，错误代码：%d\n", WSAGetLastError());
            break;
        }
    }
    closesocket(client[idx]);
}

int main() {
    SetConsoleTitle(L"聊天室服务器");

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    std::cout << "确认协议版本信息成功！" << std::endl;

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "创建socket失败！错误代码：" << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }
    std::cout << "创建socket成功！" << std::endl;

    SOCKADDR_IN addr = { 0 };
    addr.sin_family = AF_INET; // IPv4
    addr.sin_port = htons(10000);
    addr.sin_addr.S_un.S_addr = inet_addr("192.168.56.1");

    bind(sock, (SOCKADDR*)&addr, sizeof(addr));
    listen(sock, 5);
    std::cout << "监听成功！" << std::endl;

    for (int i = 0; i < NUM; i++) {
        SOCKADDR_IN clientAddr;
        int len = sizeof(clientAddr);
        client[i] = accept(sock, (SOCKADDR*)&clientAddr, &len);
        if (client[i] == INVALID_SOCKET) {
            std::cerr << "接受连接失败，错误代码：" << WSAGetLastError() << std::endl;
            closesocket(sock);
            WSACleanup();
            return -1;
        }
        std::cout << "接受连接成功！" << std::endl;

        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)tongxin, (LPVOID)i, 0, NULL);
        {
            std::lock_guard<std::mutex> lock(clientMutex);
            clientNum++;
        }
    }

    closesocket(sock);
    WSACleanup();
    std::cout << "服务器已关闭！" << std::endl;
    return 0;
}
