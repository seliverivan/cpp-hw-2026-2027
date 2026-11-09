
#include "operations/Operation.h"
#include "plugins/PluginEntry.h"
#include <cmath>
#include <stdexcept>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <vector>

class PowOperation final : public Operation {
public:
    std::string getName() const override { return "^"; }
    int getArity() const override { return 2; }
    int getPriority() const override { return 4; }

    Fixity getFixity() const override {
        return Fixity::Infix;
    }

    Associativity getAssociativity() const override {
        return Associativity::Right;
    }

    double execute(const std::vector<double>& args) const override {
        if (args.size() != 2)
            throw std::invalid_argument("^ requires 2 arguments");

        double result = std::pow(args[0], args[1]);

        if (std::isnan(result))
            throw std::domain_error("Invalid power");

        if (!std::isfinite(result))
            throw std::overflow_error("Power overflow");

        return result;
    }
};


Operation* createPluginInstance() {
    return new PowOperation();
}