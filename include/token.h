#pragma once

#include <string>

typedef enum {
    None,
    Identifier,
    Integer,
    Colon,
    String,
    Char,
    EndOfFile
} TokenType;

typedef unsigned long long u64;

class Token {
    public:
    TokenType type;
    std::string value;
    u64 row, column;

    Token();
    Token(TokenType type, std::string value,
          u64 row, u64 column);

    Token(TokenType type, u64 row, u64 column);
    Token(TokenType type);
};
