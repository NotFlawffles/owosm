#include <cctype>
#include "../include/lexer.h"


Lexer::Lexer(void) {}

Lexer::Lexer(std::string fileName, std::string content) {
    this->fileName = fileName;
    this->content = content;
    current = this->content[index];
}

Token Lexer::next(void) {
    skipWhitespace();

    if (isalpha(current) || current == '_')
        return lexIdentifier();

    else if (isdigit(current))
        return lexNumeric();

    return Token(EndOfFile);
}

Token Lexer::lexIdentifier(void) {
    std::string value = std::string();
    ull row = this->row, column = this->column;
    
    while (isalnum(current) || current == '_') {
        value.push_back(current);
        advance();
    }

    return Token(Identifier, value, row, column);
}

Token Lexer::lexNumeric(void) {
    std::string value = std::string();
    ull row = this->row, column = this->column;
    
    while (isdigit(current) || current == 'x' || current == 'b') {
        value.push_back(current);
        advance();
    }

    return Token(Integer, value, row, column);
}

Token Lexer::advanceWithToken(Token token) {
    advance();
    return token;
}

void Lexer::advance(void) {
    current = content[++index];
    column++;
}

void Lexer::skipWhitespace(void) {
    while (current == ' ' || current == '\t' || current == '\n') {
        if (current == '\n') {
            row++;
            column = 0;
        }

        advance();
    }
};
