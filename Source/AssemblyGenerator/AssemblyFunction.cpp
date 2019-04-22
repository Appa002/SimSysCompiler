#include <utility>
#include <utils.h>
#include <AssemblyGenerator/DataStructureMovement.h>
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

void ACC::AssemblyFunction::createStructure(ACC::Location where, std::string structure, std::vector<ACC::Location> data) {
    auto structureStack = generateStructureStack(structure);
    size_t stackSize = getStructureStackSize(structureStack);

    if (where.accessMethod == AccessMethod::STACK_TOP) {
        this->requiredStackSize += stackSize;
        for (const auto &d : data) {
            if (d.accessMethod == AccessMethod::IMMEDIAT){
                this->writeLine(Movs::imm2st(d));
                structureStack.pop();
            }

            if (d.accessMethod == AccessMethod::SBP_OFFSET)
                this->writeLine(Movs::bp2st(d, structureStack));

            if(d.accessMethod == AccessMethod::REGISTER){
                this->writeLine(Movs::r2st(d));
                structureStack.pop();
            }
        }

    } else if (where.accessMethod == AccessMethod::SBP_OFFSET) {
        if(where.offsetInfo >= 0)
            this->requiredStackSize += stackSize;

        for (const auto &d : data) {
            if (d.accessMethod == AccessMethod::IMMEDIAT){
                this->writeLine(Movs::imm2bp(d, where));
                structureStack.pop();
            }

            if(d.accessMethod == AccessMethod::REGISTER){
                structureStack.pop();
                this->writeLine(Movs::r2bp(where, d));
            }
        }
    } else if(where.accessMethod == AccessMethod::STACK_OFFSET){
        if(where.offsetInfo >= 0)
            this->requiredStackSize += stackSize;
        for (const auto& d : data){
            if (d.accessMethod == AccessMethod::IMMEDIAT){
                this->writeLine(Movs::imm2so(d, where));
                structureStack.pop();
            }
        }
    } else if(where.accessMethod == AccessMethod::REGISTER){
        for (const auto& d : data){
            if(d.accessMethod == AccessMethod::SBP_OFFSET){
                this->writeLine(Movs::bp2r(d, where));
                structureStack.pop();
            }
        }
    }
}

