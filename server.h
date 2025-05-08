#ifndef SERVER_H
#define SERVER_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
// Windows doesn't define socklen_t by default
typedef int socklen_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct SERVER {
    int domain;
    int service;
    int protocol;
    unsigned long interface_addr;
    int port;
    int backlog;
    int socket;
    struct sockaddr_in address; //IPv4
    void (*launch) (struct SERVER* server);
} server;

server server_constructor(int domain, int service, int protocol, unsigned long interface_addr, int port, int backlog, void (*launch)(struct SERVER* server)) {
    server server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface_addr = interface_addr;
    server.port = port;
    server.backlog = backlog;
    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface_addr);
    server.socket = socket(domain, service, protocol);
    if (!server.socket) {
        perror("SOCKET CONNECTION FAILED.\n");
        exit(EXIT_FAILURE);
    }
    if (bind(server.socket, (struct sockaddr*) &server.address, sizeof(server.address)) < 0) {
#ifdef _WIN32
        printf("SOCKET BINDING FAILED: %d\n", WSAGetLastError());
#else
        perror("SOCKET BINDING FAILED");
#endif
        exit(EXIT_FAILURE);
    }
    if (listen(server.socket, server.backlog) < 0) {
        perror("SERVER LISTENING FAILED\n");
        exit(EXIT_FAILURE);
    }
    server.launch = launch;
    return server;
}

#endif