cmake_minimum_required(VERSION 3.24)
project(port_scanner_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(port_scanner_cpp main.cpp ArgumentParser.cpp Panic.cpp)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests test.cpp ArgumentParser.cpp Panic.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)