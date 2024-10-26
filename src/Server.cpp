#include "Server.h"
#include "Logger.h"
#include <iostream>

Server::Server(int port) : port_(port), running_(false) {}

Server::~Server() {
    stop();
}

void Server::start() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        logError("WSAStartup failed in Server.");
        return;
    }

    serverSocket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket_ == INVALID_SOCKET) {
        logError("Socket creation failed in Server.");
        WSACleanup();
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port_);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket_, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        logError("Bind failed in Server.");
        closesocket(serverSocket_);
        WSACleanup();
        return;
    }

    running_ = true;
    listenerThread_ = std::thread(&Server::listenForPackets, this);
}

void Server::stop() {
    running_ = false;
    if (listenerThread_.joinable()) {
        listenerThread_.join();
    }
    closesocket(serverSocket_);
    WSACleanup();
}

void Server::listenForPackets() {
    char buffer[512];
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    while (running_) {
        int bytesReceived = recvfrom(serverSocket_, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&clientAddr, &clientAddrSize);
        if (bytesReceived == SOCKET_ERROR) {
            logError("Receive failed in Server.");
            continue;
        }

        buffer[bytesReceived] = '\0';
        std::string packetData(buffer);
        analyzer_.analyzePacket(packetData);
    }
}
