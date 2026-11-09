#include "ast/OperationNode.h"

double OperationNode::evaluate() const{
    std::vector<double> values;
    values.reserve(arguments.size());

    for (const auto& argument : arguments) {
        values.push_back(argument->evaluate());
    }

    return operation->execute(values);
}