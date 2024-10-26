#include "PacketGenerator.h"
#include "Logger.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <WinSock2.h>
#include <cstdlib> // For rand()
#include <Ws2tcpip.h>


#pragma comment(lib, "ws2_32.lib")

PacketGenerator::PacketGenerator(const std::string& targetIp, int port)
    : targetIp_(targetIp), port_(port), running_(false) {}

PacketGenerator::~PacketGenerator() {
    stop();
}

void PacketGenerator::start(int numConnections) {
    running_ = true;
    for (int i = 0; i < numConnections; ++i) {
        generatorThreads_.emplace_back(&PacketGenerator::generatePackets, this, i);
    }
}

void PacketGenerator::stop() {
    running_ = false;
    for (auto& thread : generatorThreads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    generatorThreads_.clear();
}

void PacketGenerator::generatePackets(int id) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        logError("WSAStartup failed in PacketGenerator.");
        return;
    }

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == INVALID_SOCKET) {
        logError("Socket creation failed in PacketGenerator.");
        WSACleanup();
        return;
    }

    sockaddr_in targetAddr;
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_port = htons(port_);
    inet_pton(AF_INET, targetIp_.c_str(), &targetAddr.sin_addr);

    while (running_) {
        const int packetSize = 100; // Fixed packet size for simplicity
        char packetData[100];

        // Randomly determine if this packet is "malicious"
        bool sendMalicious = (rand() % 10) < 6; // 20% chance to send malicious packet
        if (sendMalicious) {
            snprintf(packetData, sizeof(packetData), "Connection %d: malicious attack data", id);
        } else {
            snprintf(packetData, sizeof(packetData), "Connection %d: normal packet data", id);
        }

        int sent = sendto(sockfd, packetData, packetSize, 0, (sockaddr*)&targetAddr, sizeof(targetAddr));
        if (sent == SOCKET_ERROR) {
            logError("Failed to send packet in PacketGenerator (Connection " + std::to_string(id) + ").");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Fixed delay
    }

    closesocket(sockfd);
    WSACleanup();
}
