#pragma once

#include <string>

typedef enum {
    None,
    Identifier,
    Integer,
    EndOfFile
} TokenType;

typedef unsigned long long ull;

class Token {
    public:
    TokenType type;
    std::string value;
    ull row, column;

    Token();
    Token(TokenType type, std::string value,
          ull row, ull column);

    Token(TokenType type, ull row, ull column);
    Token(TokenType type);
};
