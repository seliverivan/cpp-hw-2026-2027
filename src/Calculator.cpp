#include "Calculator.h"

namespace fs = std::filesystem;

fs::path getExecutableDirectory() {
    std::wstring buffer(32768, L'\0');

    DWORD length = GetModuleFileNameW(
        nullptr,
        buffer.data(),
        static_cast<DWORD>(buffer.size())
    );

    if (length == 0 || length >= buffer.size()) {
        throw std::runtime_error(
            "Cannot determine executable directory"
        );
    }

    buffer.resize(length);

    return fs::path(buffer).parent_path();
}

void registerBuiltInOperations(OperationRegistry& registry) {
    registry.registerOperation(std::make_unique<Add>());
    registry.registerOperation(std::make_unique<Substract>());
    registry.registerOperation(std::make_unique<Multiply>());
    registry.registerOperation(std::make_unique<Divide>());
    registry.registerOperation(std::make_unique<UnaryMinus>());
}

void runCalculator(
    const Lexer& lexer,
    Parser& parser
) {
    std::cout << "\nCalculator started\n";
    std::cout << "Enter an expression ('exit' to quit)\n\n";

    std::string expression;

    while (true) {
        std::cout << "> ";

        if (!std::getline(std::cin, expression)) {
            break;
        }

        if (expression == "exit") {
            break;
        }

        if (expression.empty()) {
            continue;
        }

        try {
            auto tokens = lexer.tokenize(expression);
            auto tree = parser.parse(std::move(tokens));

            std::cout << "= " << tree->evaluate() << '\n';
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
        catch (...) {
            std::cerr << "Unknown calculation error\n";
        }
    }
}

int main() {
    try {
        OperationRegistry registry;

        registerBuiltInOperations(registry);

        PluginManager pluginManager(registry);

        const fs::path pluginDirectory =
            getExecutableDirectory() / "plugins";

        pluginManager.loadPlugins(pluginDirectory);

        Lexer lexer(registry.getOperatorNames());
        Parser parser(registry);

        runCalculator(lexer, parser);
    }
    catch (const std::exception& e) {
        std::cerr << "Initialization error: "
            << e.what() << '\n';

        return 1;
    }

    return 0;
}