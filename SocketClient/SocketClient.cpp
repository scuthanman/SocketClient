// SocketClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

void EchoClient()
{
    WSADATA ws_data;
    WSAStartup(MAKEWORD(2, 2), &ws_data);

    sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = PF_INET;
    InetPtonA(PF_INET, "127.0.0.1", &sock_addr.sin_addr.s_addr);
    sock_addr.sin_port = htons(1234);

    int num = 1;
    while (num > 0) {

        SOCKET client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

        // int connect(SOCKET sock, const struct sockaddr *serv_addr, int addrlen);
        connect(client_socket, (sockaddr*)&sock_addr, sizeof(SOCKADDR));

        char sz_content[MAX_PATH] = { "hello i am client!" };
        int send_num = send(client_socket, sz_content, strlen(sz_content) + 1, 0);

        char sz_content_recv[MAX_PATH] = { 0 };
        int recv_num = recv(client_socket, sz_content_recv, MAX_PATH, NULL);

        printf("Message from server : %s \n", sz_content_recv);

        closesocket(client_socket);

        num--;
    }
    
    WSACleanup();

    system("pause");
}

void FileTransClient() {

    WSADATA ws_data;
    WSAStartup(MAKEWORD(2, 2), &ws_data);

    sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = PF_INET;
    sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sock_addr.sin_port = htons(1234);

    SOCKET client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    connect(client_socket, (sockaddr*)&sock_addr, sizeof(sock_addr));

    char buff[1024] = { 0 };
    int nCount = 0;

    FILE* file = NULL;
    file = fopen("E:\\1.avi", "wb");
    if (file) {
        nCount = recv(client_socket, buff, 1024, 0);
        while (nCount > 0) {
            fwrite(buff, 1, nCount, file);
            nCount = recv(client_socket, buff, 1024, 0);
        }
        fclose(file);
    }
    closesocket(client_socket);
    WSACleanup();
    //system("pause");
}

void UdpEchoClient() {
    WSADATA ws_data;
    WSAStartup(MAKEWORD(2, 2), &ws_data);

    SOCKET client_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    sockaddr_in server_addr;
    server_addr.sin_family = PF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(1234);

    sockaddr_in from_addr;
    int from_size = sizeof(from_addr);
    int count = 3;
    while (count > 0) {
        char buffer[1024] = "1234";
        sendto(client_socket, buffer, strlen(buffer), 0, (sockaddr*)&server_addr, sizeof(server_addr));
        int recv_len = recvfrom(client_socket, buffer, 1024, 0, (sockaddr*)&from_addr, &from_size);
        buffer[recv_len] = 0;
        printf("Message form server: %s\n", buffer);
        count--;
    }
    system("pause");
}

int main() {
    UdpEchoClient();
    return 0;
}