#pragma once

#include <string>
#include <vector>
#include "Fixity.h"
#include "Associativity.h"

class Operation {
public:
    virtual ~Operation() = default;

    virtual std::string getName() const = 0;
    virtual int getArity() const = 0;
    virtual int getPriority() const = 0;

    virtual Fixity getFixity() const = 0;
    virtual Associativity getAssociativity() const = 0;

    virtual double execute(const std::vector<double>& args ) const = 0;
};