#pragma once

#include <string>

enum class TokenType {
    Number,
    Operator,
    Identifier,
    LeftParen,
    RightParen,
    Comma,
    End
};

struct Token {
    TokenType type;
    std::string value;
};