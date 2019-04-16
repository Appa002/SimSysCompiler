//
// Created by a_mod on 02.03.2019.
//

#include "OperatorGenerators.h"
#include <utils.h>

/*
 * operator layout:
 * iprint <constant>
 *        lhs          rhs
 *
 * assembly layout:
 *
 * sub rsp, 8 ; reserve 8 ytes of data on the stack
 *
 * mov rax, 1 ; sys_write
 * mov rdi, 1 ; stdout
 * mov dword [rsp], 0x34333231
*  mov dword [rsp + 4], 0x38373635

 * mov rsi, rsp
 * mov rdx, <size of ascii representation>
 * syscall
 * */
void ACC::OpGenerators::iPrint(ACC::Operator *op, Assembly& assembly) {
    auto& targetFunction = assembly.fetchFunction();
    std::string value = std::to_string(op->lhs);
    value += "\n";

    std::vector<Location> snippets;
    dWordAlignT<std::string, char>(value, [&](std::vector<char> packet){
        for(auto itr = packet.rbegin(); itr != packet.rend(); ++itr){
            Location l(AccessMethod::CONSTANT);
            l.constant = *itr;
            snippets.push_back(l);
        }
    });

    assembly.createStructure(Location(AccessMethod::STACK_TOP), std::to_string(value.size()), snippets);
    targetFunction.mov("rax", "1", "sys_write");
    targetFunction.writeLine("mov rdi, 1 ; stdout");
    targetFunction.writeLine("mov rsi, rsp");
    targetFunction.writeLine("mov rdx, " + std::to_string(value.size()));
    targetFunction.writeLine("syscall");
}

void ACC::OpGenerators::exit(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& targetFunction = assembly.fetchFunction();
    targetFunction.writeLine("mov rax, 60 ;sys_exit");
    targetFunction.writeLine("mov rdi, "+std::to_string(op->lhs)+" ; exit code");
    targetFunction.writeLine("syscall");
}

void ACC::OpGenerators::iAddOp(ACC::Operator *op, ACC::Assembly &assembly) {

}
