#pragma once

#include "Token.h"
#include <string>
#include <vector>

class Lexer {
private:
    std::vector<std::string> operators;

    Token readNumber(std::string::const_iterator& it, std::string::const_iterator end) const;

    Token readIdentifier(std::string::const_iterator& it, std::string::const_iterator end) const;

    Token readOperator(std::string::const_iterator& it, std::string::const_iterator end) const;

public:
    explicit Lexer(std::vector<std::string> operators);

    std::vector<Token> tokenize(const std::string& expression) const;
};