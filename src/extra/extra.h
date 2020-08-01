#pragma once
#include <iostream>

namespace ext {
    int err(char* msg) {
        std::cerr << *msg << std::endl;
        exit(-1);
    }
}