#pragma once

#include "ExpressionNode.h"
#include "operations/Operation.h"

#include <memory>
#include <vector>

class OperationNode : public ExpressionNode {
private:
    const Operation* operation;

    std::vector<std::unique_ptr<ExpressionNode>> arguments;

public:

    OperationNode(const Operation* operation, std::vector<std::unique_ptr<ExpressionNode>> arguments) : operation(operation), arguments(std::move(arguments)) {};

    double evaluate() const override;
};