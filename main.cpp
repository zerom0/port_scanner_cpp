#include "ArgumentParser.h"
#include "Panic.h"

#include <arpa/inet.h>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

void scanPort(const std::string &address, unsigned short port) {
    int connectSocket = 0;
    struct sockaddr_in ipOfServer;

    if ((connectSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        panic("Socket not created");
    }
    // TODO: Set timeout, but how? Nonblocking with timer?

    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(port);
    ipOfServer.sin_addr.s_addr = inet_addr(address.c_str());

    std::stringstream stringstream;
    if (connect(connectSocket, (struct sockaddr *) &ipOfServer, sizeof(ipOfServer)) < 0) {
        stringstream << "Port " << port << " is not open 🛑" << std::endl
                     << std::flush;
    } else {
        stringstream << "Port " << port << " is open ✅" << std::endl
                     << std::flush;
        close(connectSocket);
    }
    std::cout << stringstream.str();
}

void scanPorts(const std::string &address, const std::vector<uint16_t> &ports) {
    std::vector<std::thread> joinables;
    for (auto port: ports) {
        joinables.emplace_back([address, port]() { scanPort(address, port); });
    }
    for (auto &joinable: joinables) {
        joinable.join();
    }
}

int main(int argc, char **argv) {
    if (argc != 4) {
        panic("Usage: port_scanner_cpp <ip-address> [-s <port>] [-r <port-range>] [-l <port-list>]");
    }

    auto address = std::string(argv[1]);
    auto mode = std::string(argv[2]);
    auto portSpec = std::string(argv[3]);

    std::vector<uint16_t> ports;
    if (mode == "-s") {
        ports = parseSinglePort(portSpec);
    } else if (mode == "-r") {
        ports = parsePortRange(portSpec);
    } else if (mode == "-l") {
        ports = parsePortList(portSpec);
    } else {
        panic("Invalid arguments");
    }

    scanPorts(address, ports);
}
