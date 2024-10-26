#include "PacketGenerator.h"
#include <cstdlib>
#include <ctime>
#include <string>

PacketGenerator::PacketGenerator() {
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed random number generator
}

std::string PacketGenerator::generatePacket() {
    // Randomly decide if the packet is normal or malicious
    bool isMalicious = std::rand() % 5 == 0; // 20% chance to be malicious
    std::string packetData;

    if (isMalicious) {
        packetData = "Connection " + std::to_string(std::rand() % 100) + ": malicious attack data";
    } else {
        packetData = "Connection " + std::to_string(std::rand() % 100) + ": normal packet data";
    }

    return packetData;
}
