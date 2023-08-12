#include "../include/compiler.h"
#include <iostream>


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "expected file name argument." << std::endl;
        return 1;
    }

    compile(argv[1]);
}
