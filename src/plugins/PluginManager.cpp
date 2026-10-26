#include "plugins/PluginManager.h"
#include "plugins/PluginOperation.h"

#include <Windows.h>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

void PluginManager::loadPlugins(
    const fs::path& directory
) {
    if (!fs::exists(directory)) {
        fs::create_directories(directory);
        return;
    }

    for (const auto& entry :
        fs::directory_iterator(directory)) {

        if (!entry.is_regular_file() ||
            entry.path().extension() != L".dll") {
            continue;
        }

        try {
            HMODULE handle = LoadLibraryW(
                entry.path().c_str()
            );

            if (!handle) {
                throw std::runtime_error("LoadLibrary failed");
            }

            // Временный владелец HMODULE
            auto releaseModule = [](HMODULE h) {
                if (h) FreeLibrary(h);
                };

            std::unique_ptr<
                std::remove_pointer_t<HMODULE>,
                decltype(releaseModule)
            > moduleGuard(handle, releaseModule);

            auto library =
                std::make_shared<PluginLibrary>(handle);

            moduleGuard.release();

            auto create = reinterpret_cast<CreateOperation>(
                GetProcAddress(handle, "createOperation")
                );

            auto destroy = reinterpret_cast<DestroyOperation>(
                GetProcAddress(handle, "destroyOperation")
                );

            auto execute = reinterpret_cast<ExecuteOperation>(
                GetProcAddress(handle, "executeOperation")
                );

            if (!create || !destroy || !execute) {
                throw std::runtime_error("Missing exports");
            }

            Operation* raw = create();

            if (!raw) {
                throw std::runtime_error("Creation failed");
            }

            std::unique_ptr<Operation, DestroyOperation>
                implementation(raw, destroy);

            auto operation = std::make_unique<PluginOperation>(
                library,
                std::move(implementation),
                execute
            );

            std::string name = operation->getName();

            registry.registerOperation(std::move(operation));

            std::cout << "Loaded: " << name << '\n';
        }
        catch (const std::exception& e) {
            std::cerr << "Plugin error: "
                << e.what() << '\n';
        }
    }
}