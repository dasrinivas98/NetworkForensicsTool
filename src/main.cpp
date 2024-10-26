#include "Server.h"
#include "PacketGenerator.h"
#include <chrono>
#include <thread>

int main() {
    Server server(8080);
    server.start();

    PacketGenerator generator("127.0.0.1", 8080);
    generator.start(100); // Simulate 100 connections

    std::this_thread::sleep_for(std::chrono::seconds(10)); // Run for 10 seconds

    generator.stop();
    server.stop();
    return 0;
}
