#include "parser/Parser.h"
#include "ast/NumberNode.h"
#include "ast/OperationNode.h"

#include <stdexcept>
#include <string>

const Token& Parser::current() const {
    if (position >= tokens.size()) {
        throw std::runtime_error("Unexpected end of expression");
    }

    return tokens[position];
}

void Parser::advance() {
    if (position < tokens.size()) {
        ++position;
    }
}

std::unique_ptr<ExpressionNode> Parser::parsePrimary() {
    const Token& token = current();

    if (token.type == TokenType::Operator) {
        const Operation* operation =
            registry.getOperation(token.value, Fixity::Prefix, 1);

        if (!operation) {
            throw std::runtime_error(
                "Unexpected operator: " + token.value
            );
        }

        advance();

        auto argument = parseExpression(
            operation->getPriority()
        );

        std::vector<std::unique_ptr<ExpressionNode>> args;
        args.push_back(std::move(argument));

        return std::make_unique<OperationNode>(
            operation,
            std::move(args)
        );
    }

    if (token.type == TokenType::Number) {
        double value = std::stod(token.value);
        advance();

        return std::make_unique<NumberNode>(value);
    }

    if (token.type == TokenType::LeftParen) {
        advance();

        auto node = parseExpression(0);

        if (current().type != TokenType::RightParen) {
            throw std::runtime_error("Expected ')'");
        }

        advance();
        return node;
    }
    if (token.type == TokenType::Identifier) {
        std::string name = token.value;
        advance();

        if (current().type != TokenType::LeftParen) {
            throw std::runtime_error(
                "Expected '(' after function: " + name
            );
        }

        advance();

        std::vector<std::unique_ptr<ExpressionNode>> args;


        if (current().type != TokenType::RightParen) {
            while (true) {
                args.push_back(parseExpression(0));

                if (current().type == TokenType::Comma) {
                    advance();
                    continue;
                }

                break;
            }
        }

        if (current().type != TokenType::RightParen) {
            throw std::runtime_error(
                "Expected ')' after function arguments"
            );
        }

        advance(); 

        const Operation* operation = registry.getOperation(
            name,
            Fixity::Function,
            static_cast<int>(args.size())
        );

        if (!operation) {
            throw std::runtime_error(
                "Unknown function or invalid argument count: " + name
            );
        }

        return std::make_unique<OperationNode>(
            operation,
            std::move(args)
        );
    }

    throw std::runtime_error(
        "Unexpected token: " + token.value
    );
}

std::unique_ptr<ExpressionNode> Parser::parseExpression(int minPriority) {
    auto left = parsePrimary();

    while (current().type == TokenType::Operator) {
        const std::string name = current().value;

        const Operation* operation =
            registry.getOperation(name, Fixity::Infix, 2);

        if (!operation) {
            throw std::runtime_error("Unknown binary operator: " + name);
        }

        int priority = operation->getPriority();

        if (priority < minPriority) {
            break;
        }

        int nextMinPriority = priority + (operation->getAssociativity() == Associativity::Left ? 1 : 0);

        advance();

        auto right = parseExpression(nextMinPriority);

        std::vector<std::unique_ptr<ExpressionNode>> args;
        args.push_back(std::move(left));
        args.push_back(std::move(right));

        left = std::make_unique<OperationNode>(operation, std::move(args));
    }

    return left;
}

std::unique_ptr<ExpressionNode> Parser::parse(
    std::vector<Token> input
) {
    tokens = std::move(input);
    position = 0;

    if (tokens.empty()) {
        throw std::runtime_error("Empty token sequence");
    }

    auto result = parseExpression(0);

    if (current().type != TokenType::End) {
        throw std::runtime_error(
            "Unexpected token after expression: " +
            current().value
        );
    }

    return result;
}