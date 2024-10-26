#include "Server.h"
#include "PacketAnalyzer.h"
#include "PacketGenerator.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>

Server::Server() : packetGenerator(), packetAnalyzer() {}

void Server::receivePackets() {
    for (int i = 0; i < 100; ++i) { // Simulate 100 packet receptions
        // Generate a packet
        std::string packetData = packetGenerator.generatePacket();
        int packetSize = static_cast<int>(packetData.size());
        
        // Get current timestamp
        std::time_t now = std::time(nullptr);
        std::string timestamp = std::ctime(&now);
        timestamp.pop_back(); // Remove the newline character

        // Analyze the received packet
        packetAnalyzer.analyzePacket(packetData, packetSize, timestamp);

        // Delay for 0.5 seconds before generating the next packet
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
