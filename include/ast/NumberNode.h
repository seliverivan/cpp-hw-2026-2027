#pragma once

#include "ExpressionNode.h"

class NumberNode : public ExpressionNode {
private:
    double value;

public:
    explicit NumberNode(double value) : value(value) {};

    double evaluate() const override;
};