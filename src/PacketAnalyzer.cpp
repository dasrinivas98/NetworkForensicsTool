#include "PacketAnalyzer.h"
#include <iostream>
#include <vector>
#include <windows.h> // Include Windows header for SetConsoleTextAttribute

PacketAnalyzer::PacketAnalyzer() {}

void PacketAnalyzer::analyzePacket(const std::string& packetData) {
    if (isMalicious(packetData)) {
        // Set console text color to red for malicious packets
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "Malicious Packet Detected: " << packetData << std::endl;
        // Reset console text color to default (white)
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << "Received Packet: " << packetData << std::endl;
    }
}

bool PacketAnalyzer::isMalicious(const std::string& packetData) {
    // Example patterns for malicious detection
    std::vector<std::string> maliciousPatterns = {
        "malicious", "attack", "exploit", "hack", "unauthorized"
    };

    // Check if the packetData contains any malicious patterns
    for (const auto& pattern : maliciousPatterns) {
        if (packetData.find(pattern) != std::string::npos) {
            return true; // Malicious packet found
        }
    }
    return false; // No malicious patterns found
}
