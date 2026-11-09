
#include "operations/Operation.h"
#include "plugins/PluginEntry.h"
#include <cmath>
#include <stdexcept>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <vector>


class LogOperation final : public Operation {
public:
    std::string getName() const override { return "log"; }
    int getArity() const override { return 1; }
    int getPriority() const override { return 0; }

    Fixity getFixity() const override {
        return Fixity::Function;
    }

    Associativity getAssociativity() const override {
        return Associativity::Left;
    }

    double execute(const std::vector<double>& args) const override {
        if (args.size() != 1)
            throw std::invalid_argument("log requires 1 argument");

        if (args[0] <= 0)
            throw std::domain_error("Logarithm domain error");

        return std::log(args[0]);
    }
};

Operation* createPluginInstance() {
    return new LogOperation();
}