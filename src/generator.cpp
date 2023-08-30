#include "../include/generator.h"
#include <string>
#include <fstream>
#include <vector>


Generator::Generator(std::string fileName, std::string content) {
    this->lexer = Lexer(fileName, content);
    this->current = this->lexer.next();
}

void Generator::generate(void) {
    preprocess();

    while (current.type != EndOfFile) {
        if (current.type == String) {
            generateString();
            continue;
        } else if (current.type == Identifier && lookupTable.count(current.value) == 0) {
            std::string name = current.value;
            current = lexer.next();
            
            if (current.type == Colon)
                current = lexer.next(); 
            
            else
                program.push_back(labels[name]);

            continue;
        }

        else    
            program.push_back(generateNext());

        current = lexer.next();
    }

    std::ofstream file(getOutName(), std::ios::out | std::ios::binary);
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

void Generator::generateString(void) {
    u16 size = current.value.size();

    program.push_back(size);
    program.push_back(Alloc);

    for (u16 i = 0; i < size; i++) {
        program.push_back(current.value.at(i));
        program.push_back(Str);
        program.push_back(0x1);
        program.push_back(Pop);
        program.push_back(0x1);
        program.push_back(Add);
    }

    program.push_back(size);
    program.push_back(Sub);
    current = lexer.next();
}

void Generator::preprocess(void) {
    Lexer lexer = this->lexer;
    Token current = this->current;
    u16 counter = 0;

    while (current.type != EndOfFile) {
        if (current.type == Identifier && lookupTable.count(current.value) == 0) {
            std::string name = current.value;
            current = lexer.next();

            if (current.type == Colon) {
                labels.insert(std::pair<std::string, u16>(name, counter));
                current = lexer.next();
            }

            else
                counter++;

            continue;
        } else if (current.type == String)
            counter += 4 + 6 * current.value.size();

        else
            counter++;

        current = lexer.next();
    }
}

std::string Generator::getOutName(void) {
    return lexer.fileName.substr(0, lexer.fileName.find('.'));
}
