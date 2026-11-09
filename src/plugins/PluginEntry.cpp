
#include "plugins/PluginEntry.h"

#include <cstdio>
#include <exception>
#include <vector>

extern "C" __declspec(dllexport)
Operation* createOperation() noexcept {
    try {
        return createPluginInstance();
    }
    catch (...) {
        return nullptr;
    }
}

extern "C" __declspec(dllexport)
void destroyOperation(Operation* operation) noexcept {
    PluginEntry::destroy(operation);
}

extern "C" __declspec(dllexport)
int executeOperation(
    Operation* operation,
    const PluginExecuteArgs* params
) noexcept {
    if (params == nullptr) {
        return 1;
    }

    return PluginEntry::execute(operation, *params);
}

namespace PluginEntry {

    void destroy(Operation* operation) noexcept {
        delete operation;
    }

    int execute(
        Operation* operation,
        const PluginExecuteArgs& params
    ) noexcept {
        try {
            if (operation == nullptr ||
                params.result == nullptr ||
                (params.args == nullptr && params.count > 0)) {
                return 1;
            }

            std::vector<double> values;

            if (params.count > 0) {
                values.assign(
                    params.args,
                    params.args + params.count
                );
            }

            *params.result = operation->execute(values);
            return 0;
        }
        catch (const std::exception& e) {
            if (params.error != nullptr && params.errorSize > 0) {
                std::snprintf(
                    params.error,
                    params.errorSize,
                    "%s",
                    e.what()
                );
            }
            return 1;
        }
        catch (...) {
            if (params.error != nullptr && params.errorSize > 0) {
                std::snprintf(
                    params.error,
                    params.errorSize,
                    "%s",
                    "Unknown plugin error"
                );
            }
            return 1;
        }
    }
}
