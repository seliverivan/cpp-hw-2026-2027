cmake_minimum_required(VERSION 3.12)

project(Calculator LANGUAGES CXX)

add_executable(Calculator
    src/Calculator.cpp

    src/operations/Add.cpp
    src/operations/Substract.cpp
    src/operations/Multiply.cpp
    src/operations/Divide.cpp
    src/operations/UnaryMinus.cpp

    src/registry/OperationRegistry.cpp

    src/lexer/Lexer.cpp

    src/parser/Parser.cpp

    src/ast/NumberNode.cpp
    src/ast/OperationNode.cpp

    src/plugins/PluginManager.cpp
    src/plugins/PluginOperation.cpp
)

target_include_directories(Calculator PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features(Calculator PRIVATE cxx_std_20)


function(add_calculator_plugin target source)
    add_library(${target} SHARED ${source})

    target_include_directories(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

    target_compile_features(${target} PRIVATE cxx_std_20)

    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/plugins"
    )
endfunction()

add_calculator_plugin(funcsin plugin_src/Sin/Sin.cpp)
add_calculator_plugin(funccos plugin_src/Cos/Cos.cpp)
add_calculator_plugin(funcexp plugin_src/Exp/Exp.cpp)
add_calculator_plugin(funcpow plugin_src/Pow/Pow.cpp)
add_calculator_plugin(funclog plugin_src/Log/Log.cpp)

add_dependencies(Calculator
    funcsin funccos funcexp funcpow funclog
)