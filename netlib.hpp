#pragma once
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <vector>

struct TCPServer {
    std::vector<int> clients;
    int socket;
    sockaddr_in address;
    
    inline TCPServer(uint16_t port) {
        start(port);
    }
    inline TCPServer() {}
    inline ~TCPServer() {
        stop();
    }

    bool setBlocking(bool blocking)
    {
    #ifdef _WIN32
        unsigned long mode = blocking ? 0 : 1;
        return (ioctlsocket(fd, FIONBIO, &mode) == 0);
    #else
        int flags = fcntl(socket, F_GETFL, 0);
        if (flags == -1) return false;
        flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
        return (fcntl(socket, F_SETFL, flags) == 0);
    #endif
    }
    void start(uint16_t port) {
        socket = ::socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = INADDR_ANY;
        bind(socket, (struct sockaddr*)&address,
            sizeof(address));
        listen(socket, 5);
    }
    void accept() {
        int clientSocket = ::accept(socket, nullptr, nullptr);
        clients.push_back(clientSocket);
    }
    inline ssize_t recv(size_t client, void* buff, size_t n) {
        return ::recv(clients[client], buff, n, 0);
    }
    inline void send(size_t client, const void* buff, size_t n) {
        ::send(clients[client], buff, n, 0);
    }
    inline void stop() {
        close(socket);
    }
};
struct TCPClient {
    int socket;
    sockaddr_in address;
    
    inline TCPClient(const char* ip, uint16_t port) {
        start(ip, port);
    }
    inline TCPClient() {}
    inline ~TCPClient() {
        stop();
    }

    bool setBlocking(bool blocking)
    {
    #ifdef _WIN32
        unsigned long mode = blocking ? 0 : 1;
        return (ioctlsocket(fd, FIONBIO, &mode) == 0);
    #else
        int flags = fcntl(socket, F_GETFL, 0);
        if (flags == -1) return false;
        flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
        return (fcntl(socket, F_SETFL, flags) == 0);
    #endif
    }
    void start(const char* ip, uint16_t port) {
        socket = ::socket(AF_INET, SOCK_STREAM, 0);
        if (socket < 0) {
            perror("socket");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0) {
            perror("inet_pton");
            close(socket);
            exit(EXIT_FAILURE);
        }
        bind(socket, (struct sockaddr*)&address,
            sizeof(address));
        
        connect(socket, (struct sockaddr*)&address,
        sizeof(address));
    }
    inline ssize_t recv(void* buff, size_t n) const {
        return ::recv(socket, buff, n, 0);
    }
    inline void send(const void* buff, size_t n) const {
        ::send(socket, buff, n, 0);
    }
    inline void stop() {
        close(socket);
    }
};