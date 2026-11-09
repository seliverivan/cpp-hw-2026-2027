#include "operations/UnaryMinus.h"
#include <stdexcept>

std::string UnaryMinus::getName() const {
    return "-";
}

int UnaryMinus::getArity() const {
    return 1;
}

int UnaryMinus::getPriority() const {
    return 3;
}

Fixity UnaryMinus::getFixity() const {
    return Fixity::Prefix;
}

Associativity UnaryMinus::getAssociativity() const {
    return Associativity::Right;
}

double UnaryMinus::execute(const std::vector<double>& args) const {
    if (args.size() != 1) {
        throw std::invalid_argument("UnaryMinus requires one argument");
    }

    return -args[0];
}