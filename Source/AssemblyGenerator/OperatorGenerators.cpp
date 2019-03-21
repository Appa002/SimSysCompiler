//
// Created by a_mod on 02.03.2019.
//

#include "OperatorGenerators.h"

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


std::string toHex (int value){
    std::stringstream stream;
    stream << std::hex << value;
    std::string str = stream.str();
    if(str.size() == 1)
        str = "0" + str;
    return str;
}

void ACC::OpGenerators::iPrint(ACC::Operator *op, Assembly& assembly) {
    std::string value = std::to_string(op->lhs);
    auto& targetFunction = assembly.fetchFunction();


    value += "\n";

    targetFunction.writeLine("sub rsp, "+ std::to_string(value.size()) + " ; reserve n bytes of data on the stack");
    targetFunction.mov("rax", "1", "sys_write");

    targetFunction.writeLine("mov rax, 1 ; sys_write");
    targetFunction.writeLine("mov rdi, 1 ; stdout");

    std::string data = "mov dword [rsp], 0x";

    size_t i = 0;
    size_t total = 0;
    size_t offset = data.size();
    for (char it : value) {
        if(i == 4){
            total++;
            data += "\nmov dword [rsp + "+std::to_string(4 * total) +"], 0x";
            offset = data.size();
            i = 0;
        }

        data.insert(offset, toHex((unsigned) it));
        i++;
    }
    targetFunction.writeLine(data);
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
