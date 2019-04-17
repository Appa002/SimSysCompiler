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

    Location location(AccessMethod::CONSTANT);

    dWordAlignT<std::string, char>(value, [&](std::vector<char> packet){
        for(auto itr = packet.rbegin(); itr != packet.rend(); ++itr){
            location.constant += *itr;
        }
    });

    assembly.createStructure(Location(AccessMethod::STACK_TOP), std::to_string(value.size()), {location});
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

void ACC::OpGenerators::iAdd(ACC::Operator *op, ACC::Assembly &assembly) {
 /*
  * mov rax, lhs
add rax, rhs
  * */

    std::string lhs = std::to_string(op->lhs);
    std::string rhs = std::to_string(op->rhs);
    auto& targetFunction = assembly.fetchFunction();

    targetFunction.mov("rax", lhs);
    targetFunction.writeLine("add rax, " + rhs);

    Location snippet(AccessMethod::SBP_OFFSET);
    snippet.offsetInfo = assembly.fetchFunction().curBpOffset;
    assembly.fetchFunction().curBpOffset += 1;

    Location store(AccessMethod::REGISTER);
    store.regInfo = Register ::rax;

    assembly.createStructure(snippet, "1", {store});

    assembly.emplaceLocation(op->result, snippet);

}

void ACC::OpGenerators::function(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& func = assembly.emplaceFunction(numberToLetterSequence(op->lhs));
}

void ACC::OpGenerators::isattr(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& func = assembly.fetchFunction();

    Location constant(AccessMethod::CONSTANT);
    constant.constant = (unsigned char)op->lhs;

    Location w(AccessMethod::STACK_OFFSET);
    w.offsetInfo = op->rhs - 1;

    assembly.createStructure(w, "1", {constant});
}

void ACC::OpGenerators::print(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& targetFunction = assembly.fetchFunction();
    auto subjectLocation = assembly.fetchLocation(op->lhs);

    if(subjectLocation.accessMethod == AccessMethod::SBP_OFFSET){
        assembly.createStructure(Location(AccessMethod::STACK_TOP), "1", {subjectLocation}); // TODO: Assumes data to be 1 byte wide
        targetFunction.mov("rax", "1", "sys_write");
        targetFunction.writeLine("mov rdi, 1 ; stdout");
        targetFunction.writeLine("mov rsi, rsp");
        targetFunction.writeLine("mov rdx, 1");
        targetFunction.writeLine("syscall");
    }

}

void ACC::OpGenerators::lattr(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& func = assembly.fetchFunction();
    Location location(AccessMethod::SBP_OFFSET);
    location.offsetInfo = (op->lhs - 1) + 8; //TODO: Assumes data to be 1 byte wide
    assembly.emplaceLocation(op->lhs, location);
}

void ACC::OpGenerators::ireturn(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& func = assembly.fetchFunction();
    func.writeLine("add rsp, "+std::to_string(func.requiredStackSize));
    func.writeLine("mov rax, " + std::to_string(op->lhs));
    func.writeLine("ret");
    assembly.emplaceFunction(assembly.functionStack.peek(1));
}

void ACC::OpGenerators::icall(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& func = assembly.fetchFunction();
    func.writeLine("call " + numberToLetterSequence(op->lhs));
}
