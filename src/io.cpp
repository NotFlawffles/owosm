#include "../include/io.h"
#include <fstream>


std::string readFile(std::string fileName) {
    std::string content;
    std::getline(std::ifstream(fileName), content, '\0');
    return content;
}
