#include "../include/generator.h"
#include <string>
#include <fstream>
#include <vector>


Generator::Generator(std::string fileName, std::string content) {
    this->lexer = Lexer(fileName, content);
    this->current = this->lexer.next();
}

void Generator::generate(void) {
    std::vector<u16> program;

    while (current.type != EndOfFile) {
        program.push_back(generateNext());
        current = lexer.next();
    }

    std::ofstream file("out", std::ios::out | std::ios::binary);
    size_t size = program.size();
    file.write((char*) &size, sizeof(size_t));
    file.write((char*) &program[0], program.size() * sizeof(u16));
    file.close();
}

u16 Generator::generateNext(void) {
    switch (current.type) {
        case Identifier:
            return lookupTable[current.value];

        case Integer:
            if (current.value.rfind("0b", 0) == 0)
                return std::stoi(current.value.substr(2), 0, 2);

            else if (current.value.rfind("0x", 0) == 0)
                return std::stoi(current.value, 0, 16);

            else
                return std::stoi(current.value, 0, 10);

        default:
            return 0;
    }
}
