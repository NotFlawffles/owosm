#include "../include/compiler.h"
#include "../include/io.h"
#include "../include/lexer.h"
#include "../include/generator.h"
#include <cstdio>
#include <fstream>


void compile(std::string fileName) {
    Generator generator(fileName, readFile(fileName));
    generator.generate();
}
