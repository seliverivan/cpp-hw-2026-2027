
#include "operations/Operation.h"
#include "plugins/PluginEntry.h"

#include <cmath>
#include <stdexcept>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <vector>

class CosOperation final : public Operation {
public:
    std::string getName() const override { return "cos"; }
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
            throw std::invalid_argument("cos requires 1 argument");

        constexpr double pi = 3.14159265358979323846;
        return std::cos(args[0] * pi / 180.0);
    }
};


Operation* createPluginInstance() {
    return new CosOperation();
}