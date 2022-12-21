#include "Panic.h"

#include <iostream>

void panic(const std::string &message) {
    std::cerr << message << std::endl;
    exit(1);
}

void todo() {
    panic("todo");
}