#include <utility>

//
// Created by a_mod on 16.03.2019.
//

#include "AssemblyFunction.h"

void ACC::AssemblyFunction::writeLine(const std::string &line) {
    code += line + "\n";
}

ACC::AssemblyFunction::AssemblyFunction(std::string sym) : symbol(std::move(sym)) {}
