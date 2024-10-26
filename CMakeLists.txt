cmake_minimum_required(VERSION 3.10)
project(NetworkForensicsTool)

set(CMAKE_CXX_STANDARD 17)

# Add executable
add_executable(NetworkForensicsTool 
    src/PacketGenerator.cpp
    src/PacketAnalyzer.cpp
    src/Server.cpp
    src/main.cpp
)

# Include directories
target_include_directories(NetworkForensicsTool PRIVATE inc)

# Link with Winsock library on Windows
if (WIN32)
    target_link_libraries(NetworkForensicsTool ws2_32)
endif()
