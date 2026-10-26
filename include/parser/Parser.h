#pragma once

#include "lexer/Token.h"
#include "ast/ExpressionNode.h"
#include "registry/OperationRegistry.h"

#include <memory>
#include <vector>

class Parser {
private:
    const OperationRegistry& registry;

    std::vector<Token> tokens;
    size_t position = 0;

    const Token& current() const;
    void advance();

    std::unique_ptr<ExpressionNode> parseExpression(int minPriority);

    std::unique_ptr<ExpressionNode> parsePrimary();

public:
    explicit Parser(const OperationRegistry& registry): registry(registry) {}

    std::unique_ptr<ExpressionNode> parse(std::vector<Token> input);
};