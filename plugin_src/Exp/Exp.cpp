#include "operations/Operation.h"
#include "plugins/PluginEntry.h"
#include <cmath>
#include <stdexcept>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <vector>

class ExpOperation final : public Operation {
public:
    std::string getName() const override { return "exp"; }
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
            throw std::invalid_argument("exp requires 1 argument");

        double result = std::exp(args[0]);

        if (!std::isfinite(result))
            throw std::overflow_error("exp overflow");

        return result;
    }
};

Operation* createPluginInstance() {
    return new ExpOperation();
}