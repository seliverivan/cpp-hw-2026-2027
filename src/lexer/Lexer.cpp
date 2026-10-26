#include "lexer/Lexer.h"

#include <algorithm>
#include <string_view>
#include <stdexcept>
#include <utility>

Lexer::Lexer(std::vector<std::string> operators): operators(std::move(operators))
{
    std::sort(
        this->operators.begin(),
        this->operators.end(),
        [](const std::string& a, const std::string& b) {
            return a.size() > b.size();
        }
    );
}

Token Lexer::readNumber(std::string::const_iterator& it, std::string::const_iterator end) const {
    std::string value;
    bool hasDot = false;

    while (it != end) {
        char c = *it;

        if (std::isdigit(static_cast<unsigned char>(c))) {
            value += c;
            ++it;
        }
        else if (c == '.' && !hasDot) {
            hasDot = true;
            value += c;
            ++it;
        }
        else {
            break;
        }
    }

    if (value == "." || value.empty()) {
        throw std::invalid_argument("Invalid number");
    }

    return { TokenType::Number, value };
}

Token Lexer::readIdentifier(std::string::const_iterator& it, std::string::const_iterator end) const {
    std::string value;

    while (it != end && (std::isalnum(static_cast<unsigned char>(*it)) || *it == '_')) {

        value += *it;
        ++it;
    }

    return { TokenType::Identifier, value };
}

Token Lexer::readOperator(std::string::const_iterator& it, std::string::const_iterator end) const {
    std::string_view remaining(&*it, end - it);

    for (const auto& op : operators) {
        if (!op.empty() && remaining.starts_with(op)) {
            it += op.size();

            return { TokenType::Operator, op };
        }
    }

    throw std::invalid_argument(
        "Unknown operator: " + std::string(1, *it)
    );
}

std::vector<Token> Lexer::tokenize(
    const std::string& expression
) const {
    auto it = expression.cbegin();
    auto end = expression.cend();

    std::vector<Token> res;

    while (it != end) {

        if (std::isspace(static_cast<unsigned char>(*it))) {
            ++it;
        }
        else if (*it == '(') {
            res.push_back({ TokenType::LeftParen, "(" });
            ++it;
        }
        else if (*it == ')') {
            res.push_back({ TokenType::RightParen, ")" });
            ++it;
        }
        else if (*it == ',') {
            res.push_back({ TokenType::Comma, "," });
            ++it;
        }
        else if (std::isdigit(static_cast<unsigned char>(*it)) ||
            *it == '.') {
            res.push_back(readNumber(it, end));
        }
        else if (std::isalpha(static_cast<unsigned char>(*it)) ||
            *it == '_') {
            res.push_back(readIdentifier(it, end));
        }
        else {
            res.push_back(readOperator(it, end));
        }
    }

    res.push_back({ TokenType::End, "" });

    return res;
}