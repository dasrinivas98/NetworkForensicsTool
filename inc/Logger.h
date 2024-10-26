// Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <ctime>

inline void logError(const std::string& message) {
    std::ofstream logFile("error_log.txt", std::ios::app);
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
        logFile << "[" << std::asctime(std::localtime(&now)) << "] " << message << std::endl;
    }
}

#endif // LOGGER_H
