#include "../include/token.h"


Token::Token(void) {}

Token::Token(TokenType type, std::string value,
             ull row, ull column)
{
    this->type = type;
    this->value = value;
    this->row = row;
    this->column = column;
}

Token::Token(TokenType type, ull row, ull column) {
    this->type = type;
    this->row = row;
    this->column = column;
}

Token::Token(TokenType type) {
    this->type = type;
}
