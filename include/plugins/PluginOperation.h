#pragma once

#include "operations/Operation.h"

#include <Windows.h>
#include <memory>
#include <string>
#include <vector>
#include <cstddef>

struct PluginLibrary {
    HMODULE handle = nullptr;

    ~PluginLibrary() {
        if (handle) {
            FreeLibrary(handle);
        }
    }

    PluginLibrary(const PluginLibrary&) = delete;
    PluginLibrary& operator=(const PluginLibrary&) = delete;

    explicit PluginLibrary(HMODULE h) : handle(h) {}
};

using CreateOperation = Operation * (*)();
using DestroyOperation = void (*)(Operation*);

using ExecuteOperation = int (*)(Operation*, const double*, std::size_t, double*, char*, std::size_t);

class PluginOperation final : public Operation {
private:
    std::shared_ptr<PluginLibrary> library;

    std::unique_ptr<Operation, DestroyOperation> implementation;
    ExecuteOperation executeFunction;

    std::string name;
    int arity;
    int priority;
    Fixity fixity;
    Associativity associativity;

public:
    PluginOperation(std::shared_ptr<PluginLibrary> library, std::unique_ptr<Operation, DestroyOperation> implementation, ExecuteOperation executeFunction);

    ~PluginOperation() override;

    PluginOperation(const PluginOperation&) = delete;
    PluginOperation& operator=(const PluginOperation&) = delete;

    std::string getName() const override;
    int getArity() const override;
    int getPriority() const override;
    Fixity getFixity() const override;
    Associativity getAssociativity() const override;

    double execute(const std::vector<double>& args) const override;
};