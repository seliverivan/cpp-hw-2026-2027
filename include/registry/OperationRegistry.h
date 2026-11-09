#pragma once

#include <map>
#include <tuple>
#include <memory>
#include <string>

#include "operations/Operation.h"

using OperationKey = std::tuple<std::string, Fixity, int>;

class OperationRegistry {
private:
    std::map<OperationKey, std::unique_ptr<Operation>> operations;

public:
    void registerOperation(std::unique_ptr<Operation> operation);

    const Operation* getOperation(const std::string& name,Fixity fixity, int arity) const;

    std::vector<std::string> getOperatorNames() const;
};