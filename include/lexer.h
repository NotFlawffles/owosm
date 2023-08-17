#pragma once

#include "token.h"

class Lexer {
    public:
    std::string fileName;
    std::string content;
    u64 index = 0, row = 1, column = 1;
    char current;

    Lexer();
    Lexer(std::string fileName, std::string content);
    Token next(void);
    
    private:
    Token lexIdentifier(void);
    Token lexNumeric(void);
    Token lexString(void);
    Token lexChar(void);
    Token advanceWithToken(Token token);
    void advance(void);
    void skipWhitespace(void);
};
