// PacketAnalyzer.h
#ifndef PACKETANALYZER_H
#define PACKETANALYZER_H

#include <string>

class PacketAnalyzer {
public:
    PacketAnalyzer();
    void analyzePacket(const std::string& packetData);

private:
    bool isMalicious(const std::string& packetData);
};

#endif // PACKETANALYZER_H
