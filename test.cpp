#include "ArgumentParser.h"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("test_correct_port_range_is_parsed", "[argument parser]") {
    REQUIRE(std::vector<uint16_t>({20, 21, 22, 23, 24, 25}) == parsePortRange("20-25"));
}