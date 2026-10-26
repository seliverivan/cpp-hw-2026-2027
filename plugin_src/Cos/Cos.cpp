
#include "operations/Operation.h"
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

extern "C" __declspec(dllexport)
Operation * createOperation() noexcept {
    try {
        return new CosOperation();
    }
    catch (...) {
        return nullptr;
    }
}

extern "C" __declspec(dllexport)
void destroyOperation(Operation * operation) noexcept {
    try {
        delete operation;
    }
    catch (...) {
    }
}

extern "C" __declspec(dllexport)
int executeOperation(
    Operation * operation,
    const double* args,
    std::size_t count,
    double* result,
    char* error,
    std::size_t errorSize
) noexcept {
    try {
        if (!operation || !result || (!args && count > 0)) {
            return 1;
        }

        std::vector<double> values;

        if (count > 0) {
            values.assign(args, args + count);
        }

        *result = operation->execute(values);
        return 0;
    }
    catch (const std::exception& e) {
        if (error && errorSize > 0) {
            std::snprintf(error, errorSize, "%s", e.what());
        }
        return 1;
    }
    catch (...) {
        if (error && errorSize > 0) {
            std::snprintf(
                error, errorSize,
                "%s", "Unknown plugin error"
            );
        }
        return 1;
    }
}