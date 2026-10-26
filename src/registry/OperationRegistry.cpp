#include "registry/OperationRegistry.h"
#include <stdexcept>
#include <algorithm>

void OperationRegistry::registerOperation(std::unique_ptr<Operation> operation) {

    if (!operation) {
        throw std::invalid_argument("Null operation");
    }

    OperationKey key{ operation->getName(), operation->getFixity(), operation->getArity()};

    auto [it, inserted] = operations.emplace(std::move(key), std::move(operation));

    if (!inserted) {
        throw std::invalid_argument("Operation already registered");
    }
}

const Operation* OperationRegistry::getOperation(const std::string& name, Fixity fixity, int arity) const {
    OperationKey key{ name, fixity, arity };
    auto it = operations.find(key);
    if (it == operations.end()) {
        return nullptr;
    }
    return it->second.get();
}


std::vector<std::string> OperationRegistry::getOperatorNames() const {
    std::vector<std::string> result;

    for (const auto& [key, operation] : operations) {
        Fixity fixity = operation->getFixity();

        if (fixity != Fixity::Infix &&
            fixity != Fixity::Prefix) {
            continue;
        }

        const std::string& name = operation->getName();

        if (std::find(result.begin(), result.end(), name) == result.end()) {
            result.push_back(name);
        }
    }

    return result;
}