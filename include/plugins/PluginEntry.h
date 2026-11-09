
#pragma once

#include "operations/Operation.h"

#include <cstddef>

struct PluginExecuteArgs {
    const double* args;
    std::size_t count;
    double* result;
    char* error;
    std::size_t errorSize;
};

// Каждая DLL предоставляет собственную реализацию
Operation* createPluginInstance();

namespace PluginEntry {
    void destroy(Operation* operation) noexcept;

    int execute(
        Operation* operation,
        const PluginExecuteArgs& params
    ) noexcept;
}
