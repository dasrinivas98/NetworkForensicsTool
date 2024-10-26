#ifndef SERVER_H
#define SERVER_H

#include "PacketGenerator.h"
#include "PacketAnalyzer.h"

class Server {
public:
    Server();
    void receivePackets();

private:
    PacketGenerator packetGenerator;
    PacketAnalyzer packetAnalyzer;
};

#endif // SERVER_H
