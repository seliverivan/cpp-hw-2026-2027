#pragma once

#include "Operation.h"

class Multiply : public Operation {
public:

    std::string getName() const override;
    int getArity() const override;
    int getPriority() const override;

    Fixity getFixity() const override;
    Associativity getAssociativity() const override;

    double execute(const std::vector<double>& args) const override;
};