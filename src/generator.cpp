#include "../include/generator.h"
#include <string>
#include <fstream>
#include <vector>


Generator::Generator(std::string fileName, std::string content) {
    this->lexer = Lexer(fileName, content);
    this->current = this->lexer.next();
}

void Generator::generate(void) {
    std::vector<i16> program;

    while (current.type != EndOfFile) {
        program.push_back(generateNext());
        current = lexer.next();
    }

    std::ofstream file("out", std::ios::out | std::ios::binary);
    size_t size = program.size();
    file.write((char*) &size, sizeof(size));
    file.write((char*) &program[0], program.size() * sizeof(i16));
    file.close();
}

i16 Generator::generateNext(void) {
    switch (current.type) {
        case Identifier:
            return lookupTable[current.value];

            break;

        case Integer:
            return std::stoi(current.value);
            break;

        default:
            return 0;
    }
}
