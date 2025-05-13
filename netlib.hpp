#pragma once

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdint.h>
#include <iostream>
static bool startedWsa=false;

#elif

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#endif

#include <stdlib.h>
#include <stdio.h>
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
        return (ioctlsocket(socket, FIONBIO, &mode) == 0);
    #else
        int flags = fcntl(socket, F_GETFL, 0);
        if (flags == -1) return false;
        flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
        return (fcntl(socket, F_SETFL, flags) == 0);
    #endif
    }
    void start(uint16_t port) {
        #ifdef _WIN32
        if(!startedWsa) {
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2,2), &wsaData);
        }
        std::cout<<"Started WSA\n";
        #endif
        socket = ::socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = INADDR_ANY;
        bind(socket, (struct sockaddr*)&address,
            sizeof(address));
        listen(socket, 5);
        std::cout<<"Listening\n";
    }
    void accept() {
        int clientSocket = ::accept(socket, nullptr, nullptr);
        clients.push_back(clientSocket);
        std::cout<<"Accepted request";
    }
    inline ssize_t recv(size_t client, void* buff, size_t n) {
        #ifdef _WIN32
        return ::recv(clients[client], (char*)buff, n, 0);
        #elif
        return ::recv(clients[client], buff, n, 0);
        #endif
    }
    inline void send(size_t client, const void* buff, size_t n) {
        #ifdef _WIN32
        ::send(clients[client], (const char*)buff, n, 0);
        #elif
        ::send(clients[client], buff, n, 0);
        #endif
    }
    inline void stop() {
        #ifdef _WIN32
        closesocket(socket);
        #elif
        close(socket);
        #endif
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
        return (ioctlsocket(socket, FIONBIO, &mode) == 0);
    #else
        int flags = fcntl(socket, F_GETFL, 0);
        if (flags == -1) return false;
        flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
        return (fcntl(socket, F_SETFL, flags) == 0);
    #endif
    }
    void start(const char* ip, uint16_t port) {
        #ifdef _WIN32
        if(!startedWsa) {
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2,2), &wsaData);
        }
        std::cout<<"Started WSA\n";
        #endif
        socket = ::socket(AF_INET, SOCK_STREAM, 0);
        if (socket < 0) {
            perror("socket");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0) {
            perror("inet_pton");
            #ifdef _WIN32
            closesocket(socket);
            #elif
            close(socket);
            #endif
            exit(EXIT_FAILURE);
        }
        
        connect(socket, (struct sockaddr*)&address,
        sizeof(address));
    }
    inline ssize_t recv(void* buff, size_t n) const {
        #ifdef _WIN32
        return ::recv(socket, (char*)buff, n, 0);
        #elif
        return ::recv(socket, buff, n, 0);
        #endif
    }
    inline void send(const void* buff, size_t n) const {
        #ifdef _WIN32
        ::send(socket, (char*)buff, n, 0);
        #elif
        ::send(socket, buff, n, 0);
        #endif
    }
    inline void stop() {
        #ifdef _WIN32
        closesocket(socket);
        #elif
        close(socket);
        #endif
    }
};