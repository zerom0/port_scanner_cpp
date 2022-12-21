#include "ArgumentParser.h"

#include "Panic.h"

#include <numeric>
#include <string>

void panic(const std::string &);

std::vector<uint16_t> parseSinglePort(const std::string &port_spec) {
    auto ports = std::vector<uint16_t>{};
    try {
        auto port = stoi(port_spec);
        ports.emplace_back(port);
    } catch (...) {
        panic("Invalid port");
    }
    return ports;
}

std::vector<uint16_t> parsePortRange(const std::string &portSpec) {
    auto separatorPos = portSpec.find('-');
    if (separatorPos == portSpec.npos) {
        panic("Invalid port range");
    }

    uint16_t from;
    try {
        auto fromSpec = portSpec.substr(0, separatorPos);
        from = std::stoi(fromSpec);
    } catch (...) {
        panic("Invalid port range (from)");
    }

    uint16_t to;
    try {
        auto toSpec = portSpec.substr(separatorPos + 1);
        to = std::stoi(toSpec);
    } catch (...) {
        panic("Invalid port range (to)");
    }

    std::vector<uint16_t> ports(to - from + 1);
    std::iota(ports.begin(), ports.end(), from);
    return ports;
}

std::vector<uint16_t> parsePortList(const std::string &port_spec) {
    todo();
    return std::vector<uint16_t>{};
}
