#include "PacketAnalyzer.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <ctime>

PacketAnalyzer::PacketAnalyzer() {}

void PacketAnalyzer::analyzePacket(const std::string& packetData, int size, const std::string& timestamp) {
    if (isMalicious(packetData)) {
        // Set console text color to red for malicious packets
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << "Malicious Packet Detected: " << packetData 
                  << " | Size: " << size 
                  << " bytes | Timestamp: " << timestamp << std::endl;
    } else {
        // Set console text color to green for normal packets
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << "Received Packet: " << packetData 
                  << " | Size: " << size 
                  << " bytes | Timestamp: " << timestamp << std::endl;
    }

    // Reset console text color to default (white)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

bool PacketAnalyzer::isMalicious(const std::string& packetData) {
    std::vector<std::string> maliciousPatterns = {
        "malicious", "attack", "exploit", "hack", "unauthorized"
    };

    for (const auto& pattern : maliciousPatterns) {
        if (packetData.find(pattern) != std::string::npos) {
            return true; // Malicious packet found
        }
    }
    return false; // No malicious patterns found
}
