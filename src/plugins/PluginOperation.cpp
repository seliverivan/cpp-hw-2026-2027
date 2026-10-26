#include "plugins/PluginOperation.h"
#include "operations/Operation.h"

#include <array>
#include <stdexcept>
#include <utility>

PluginOperation::PluginOperation(
    std::shared_ptr<PluginLibrary> library,
    std::unique_ptr<Operation, DestroyOperation> implementation,
    ExecuteOperation executeFunction
)
    : library(std::move(library)),
      implementation(std::move(implementation)),
      executeFunction(executeFunction)
{
    if (!this->library || !this->implementation ||
        !this->executeFunction) {
        throw std::invalid_argument("Invalid plugin");
    }

    name = this->implementation->getName();
    arity = this->implementation->getArity();
    priority = this->implementation->getPriority();
    fixity = this->implementation->getFixity();
    associativity = this->implementation->getAssociativity();
}
PluginOperation::~PluginOperation() = default;

std::string PluginOperation::getName() const {
    return name;
}

int PluginOperation::getArity() const {
    return arity;
}

int PluginOperation::getPriority() const {
    return priority;
}

Fixity PluginOperation::getFixity() const {
    return fixity;
}

Associativity PluginOperation::getAssociativity() const {
    return associativity;
}

double PluginOperation::execute(const std::vector<double>& args) const {
    double result = 0.0;
    std::array<char, 512> error{};

    int status = executeFunction(implementation.get(), args.data(), args.size(), &result, error.data(), error.size());

    if (status != 0) {
        throw std::runtime_error(error[0] ? error.data() : "Plugin execution failed");
    }

    return result;
}