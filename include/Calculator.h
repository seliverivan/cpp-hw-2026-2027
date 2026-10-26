#pragma once

#include "registry/OperationRegistry.h"
#include "plugins/PluginManager.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"

#include "operations/Add.h"
#include "operations/Substract.h"
#include "operations/Multiply.h"
#include "operations/Divide.h"
#include "operations/UnaryMinus.h"

#include <Windows.h>

#include <filesystem>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>