#include <utility>

//
// Created by a_mod on 16.03.2019.
//

#include "AssemblyFunction.h"


void ACC::AssemblyFunction::writeLine(const std::string &line) {
    code += line + "\n";
}

ACC::AssemblyFunction::AssemblyFunction(std::string sym) : symbol(std::move(sym)) {}

void ACC::AssemblyFunction::mov(std::string target, std::string source, ACC::SizeDefinition size, bool ptr,
        std::string comment) {
    /*
         * Cases:
         *
         * mov <size> <ptr?> [<register>], <immediate>
         * mov <size> <ptr?> [<register>], <register>
         * e.g.:
         * mov dword [rsp], 0x0a30
         * mov dword ptr [rax], 0x00
         * */

        std::string ptrStr = ptr ? ("ptr ") : ("");
        writeLine("mov " + sizeToString(size) + " " + ptrStr + "[" + target + "], " + source + " ; " + comment);

}

void ACC::AssemblyFunction::mov(std::string target, std::string source, std::string comment) {
        /*
         * Cases:
         *
         * mov <register>, <immediate>
         * mov <register>, <register>
         * e.g.:
         * mov eax, 10
         * */

        writeLine("mov " + target + ", " + source + " ; " + comment);
}

std::string ACC::AssemblyFunction::generateCode() {
    std::string out;
    out += "mov rbp, rsp\n";
    out += "sub rsp, "+ std::to_string(requiredStackSize) +"\n";
    out += code;
    return out;
}

std::string ACC::sizeToString(ACC::SizeDefinition size) {
    switch (size){
        case SizeDefinition::dowrd:
            return "dword";
        case SizeDefinition::qword:
            return "qword";
        case SizeDefinition::word:
            return "word";
        case SizeDefinition::byte:
            return "byte";
    }
    return "";
}
