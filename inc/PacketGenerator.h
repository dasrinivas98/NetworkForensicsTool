// PacketGenerator.h
#ifndef PACKETGENERATOR_H
#define PACKETGENERATOR_H

#include <string>
#include <vector>
#include <thread>

class PacketGenerator {
public:
    PacketGenerator(const std::string& targetIp, int port);
    ~PacketGenerator();

    void start(int numConnections = 100);
    void stop();

private:
    void generatePackets(int id);
    std::string targetIp_;
    int port_;
    bool running_;
    std::vector<std::thread> generatorThreads_;
};

#endif // PACKETGENERATOR_H
