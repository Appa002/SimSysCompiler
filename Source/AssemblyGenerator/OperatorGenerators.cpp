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

ACC::Snippet ACC::OpGenerators::iPrint(ACC::Operator *op, Assembly& assembly) {
    std::string value = std::to_string(op->lhs);
    value += "\n";

    std::string code = "sub rsp, "+ std::to_string(value.size()) + " ; reserve n bytes of data on the stack";
    code +=R"(
mov rax, 1 ; sys_write
mov rdi, 1 ; stdout
)";


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
    code += data + "\n";
    code += std::string("mov rsi, rsp") + "\n";
    code += "mov rdx, " + std::to_string(value.size()) + "\n";
    code += "syscall\n";

    assembly.writeToText(code);
    return Snippet(code, AccessMethod::NONE, nullptr);
}

ACC::Snippet ACC::OpGenerators::exit(ACC::Operator *op, ACC::Assembly &assembly) {
    std::string code;
    code += "mov rax, 60 ;sys_exit\n";
    code += "mov rdi, "+std::to_string(op->lhs)+" ; exit code\n";
    code += "syscall\n";
    assembly.writeToText(code);
    return Snippet(code, AccessMethod::NONE, nullptr);

}
