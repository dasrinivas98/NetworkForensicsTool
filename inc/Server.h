// Server.h
#ifndef SERVER_H
#define SERVER_H

#include "PacketAnalyzer.h"
#include <thread>
#include <WinSock2.h>

class Server {
public:
    Server(int port);
    ~Server();

    void start();
    void stop();

private:
    void listenForPackets();
    int port_;
    bool running_;
    SOCKET serverSocket_;
    std::thread listenerThread_;
    PacketAnalyzer analyzer_;
};

#endif // SERVER_H
