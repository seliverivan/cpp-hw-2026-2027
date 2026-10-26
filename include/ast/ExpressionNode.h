#pragma once

class ExpressionNode {
public:
    virtual ~ExpressionNode() = default;
    virtual double evaluate() const = 0;
};