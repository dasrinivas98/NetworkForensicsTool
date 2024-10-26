#ifndef PACKET_ANALYZER_H
#define PACKET_ANALYZER_H

#include <string>

class PacketAnalyzer {
public:
    PacketAnalyzer();
    void analyzePacket(const std::string& packetData, int size, const std::string& timestamp);
    bool isMalicious(const std::string& packetData);
};

#endif // PACKET_ANALYZER_H
