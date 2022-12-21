#pragma once

#include <vector>

std::vector<uint16_t> parseSinglePort(const std::string &port_spec);
std::vector<uint16_t> parsePortRange(const std::string &portSpec);
std::vector<uint16_t> parsePortList(const std::string &port_spec);