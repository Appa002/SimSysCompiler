//
// Created by a_mod on 16.05.2019.
//

#include "Fn.h"

void ACC::Fn::writeLine(std::string const &line) {
    code += line + "\n";
}

std::string ACC::Fn::generate() {
    std::string out;
    out += "push rbp\n";
    out += "mov rbp, rsp\n";
    out += "sub rsp, " + std::to_string(curBpOffset) + "\n";
    out += code;
    return out;
}


