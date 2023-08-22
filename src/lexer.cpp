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

    else if (current == '"')
        return lexString();

    else if (current == '\'')
        return lexChar();

    else if (current == ':')
        return advanceWithToken(Token(Colon, row, column));

    else if (current == ';') {
        while (current != '\n')
            advance();

        return next();
    }

    return Token(EndOfFile);
}

Token Lexer::lexIdentifier(void) {
    std::string value = std::string();
    u64 row = this->row, column = this->column;
    
    while (isalnum(current) || current == '_') {
        value.push_back(current);
        advance();
    }

    return Token(Identifier, value, row, column);
}

Token Lexer::lexNumeric(void) {
    std::string value = std::string();
    u64 row = this->row, column = this->column;
    
    while (isdigit(current) || current == 'x' || current == 'b') {
        value.push_back(current);
        advance();
    }

    return Token(Integer, value, row, column);
}

Token Lexer::lexString(void) {
    std::string value = std::string();
    u64 row = this->row, column = this->column;
    advance();
    
    while (current != '"') {
        if (current == '\\') {
            advance();
            
            switch (current) {
                case 'n':
                    value.push_back('\n');
                    break;

                case 't':
                    value.push_back('\t');
                    break;
            }
        } else
            value.push_back(current);

        advance();
    }

    advance();
    return Token(String, value, row, column);
}

Token Lexer::lexChar(void) {
    u64 row = this->row, column = this->column;
    advance();

    char value;

    if (current == '\\') {
        advance();
        
        switch (current) {
            case 'n':
                value = '\n';
                break;

            case 't':
                value = '\t';
                break;
        }
    } else
        value = current;

    advance();
    advance();
    return Token(Char, (std::string) {value}, row, column);
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
