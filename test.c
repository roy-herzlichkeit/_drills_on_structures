#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#endif
#include "./server.h"

void launch(server *server) {
    char buffer[33010];
#ifdef _WIN32
    // Windows init
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);
#endif
    while (1) {
        printf("===== WAITING FOR CONNECTION =====\n");
        int addrlen = sizeof(server->address);
        int new_socket = accept(server->socket, (struct sockaddr*) &server->address, (socklen_t *) &addrlen);
#ifdef _WIN32
        recv(new_socket, buffer, sizeof(buffer), 0);
#else
        read(new_socket, buffer, sizeof(buffer));
#endif
        printf("%s\n", buffer);
        char *hello = "HTTP/1.1 200 OK\r\n\r\nContent-Type: text/html\nConnection: Closed\n<html><body><h1>Los Pollos Hermanos!</h1></body></html>";
#ifdef _WIN32
        send(new_socket, hello, strlen(hello), 0);
#else
        write(new_socket, hello, strlen(hello));
#endif
    }
#ifdef _WIN32
    WSACleanup();
#endif
}

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }
#endif
    server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 5173, 10, launch);
    launch(&server);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}