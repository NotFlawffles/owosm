#include "../include/generator.h"
#include <string>
#include <fstream>
#include <vector>


Generator::Generator(std::string fileName, std::string content) {
    this->lexer = Lexer(fileName, content);
    this->current = this->lexer.next();
}

void Generator::generate(void) {
    while (current.type != EndOfFile) {
        if (current.type == Identifier && lookupTable.find(current.value) == lookupTable.end()) {
            generateLabel();
            continue;
        } else if (current.type == String) {
            generateString();
            continue;
        }
        
        program.push_back(generateNext());
        current = lexer.next();
        counter++;
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
            return generateInteger();

        case Char:
            return current.value.at(0);

        default:
            return 0;
    }
}

u16 Generator::generateInteger(void) {
    if (current.value.rfind("0b", 0) == 0)
        return std::stoi(current.value.substr(2), 0, 2);

    else if (current.value.rfind("0x", 0) == 0)
        return std::stoi(current.value, 0, 16);

    else
        return std::stoi(current.value, 0, 10);
}

void Generator::generateLabel(void) {
    std::string name = current.value;
    current = lexer.next();
    
    if (current.type == Colon) {
        current = lexer.next();
        labels.insert(std::pair<std::string, u16>(name, counter));
    } else {
        program.push_back(labels[name]);
        counter++;
    }
}

void Generator::generateString(void) {
    u16 size = current.value.size();

    program.push_back(size);
    program.push_back(Alloc);
    counter += 2;

    for (u16 i = 0; i < size; i++) {
        program.push_back(current.value.at(i));
        program.push_back(Str);
        program.push_back(0x1);
        program.push_back(Pop);
        program.push_back(0x1);
        program.push_back(Add);
        counter += 6;
    }

    program.push_back(size);
    program.push_back(Sub);
    counter += 2;
    current = lexer.next();
}
