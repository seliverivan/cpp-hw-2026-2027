
#include "operations/Operation.h"
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

extern "C" __declspec(dllexport)
Operation * createOperation() noexcept {
    try {
        return new PowOperation();
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