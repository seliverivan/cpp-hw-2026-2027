#pragma once

#include "registry/OperationRegistry.h"

#include <filesystem>

class PluginManager {
private:
    OperationRegistry& registry;

public:
    explicit PluginManager(OperationRegistry& registry): registry(registry) {}

    void loadPlugins(const std::filesystem::path& directory);
};