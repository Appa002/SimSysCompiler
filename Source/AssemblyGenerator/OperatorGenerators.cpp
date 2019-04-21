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

    Location location = Location::constant("");

    dWordAlignT<std::string, char>(value, [&](std::vector<char> packet){
        for(auto itr = packet.rbegin(); itr != packet.rend(); ++itr){
            location.constantInfo += *itr;
        }
    });

    targetFunction.createStructure(Location::stackTop(), std::to_string(value.size()), {location});
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

    Location snippet = Location::baseOffset(targetFunction.curBpOffset);
    targetFunction.curBpOffset += 8;
    targetFunction.requiredStackSize += 8;

    Location store = Location::reg(Register::rax);

    targetFunction.createStructure(snippet, "1", {store});

    assembly.emplaceLocation(op->result, snippet);

}

void ACC::OpGenerators::function(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& func = assembly.emplaceFunction(numberToLetterSequence(op->lhs));
}

void ACC::OpGenerators::isattr(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& func = assembly.fetchFunction();

    Location constant = Location::constant((unsigned char)op->lhs);

    Location w = Location::stackOffset(op->rhs - 1);
    func.createStructure(w, "1", {constant});
}

void ACC::OpGenerators::print(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& targetFunction = assembly.fetchFunction();
    auto subjectLocation = assembly.fetchLocation(op->lhs);

    targetFunction.createStructure(Location::stackTop(), "1", {subjectLocation}); // TODO: Assumes data to be 1 byte wide

    targetFunction.mov("rax", "1", "sys_write");
    targetFunction.writeLine("mov rdi, 1 ; stdout");
    targetFunction.writeLine("mov rsi, rsp");
    targetFunction.writeLine("mov rdx, 1");
    targetFunction.writeLine("syscall");

}

void ACC::OpGenerators::lattr(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& func = assembly.fetchFunction();
    Location location = Location::baseOffset((op->lhs - 1) + 8); //TODO: Assumes data to be 1 byte wide
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
    Location returnLocation = Location::reg(Register::rax);

    Location location = Location::baseOffset(-(offset_t)func.curBpOffset);
    func.curBpOffset += 8;
    func.requiredStackSize += 8;


    func.createStructure(location, "1", {returnLocation});
    assembly.emplaceLocation(op->result, location);
}

void ACC::OpGenerators::ret(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& func = assembly.fetchFunction();
    func.writeLine("add rsp, "+std::to_string(func.requiredStackSize));

    Location subjectLocation = assembly.fetchLocation(op->lhs);

    Location rax = Location::reg(Register::rax);

    func.createStructure(rax, "1", {subjectLocation});

    func.writeLine("ret");
    assembly.emplaceFunction(assembly.functionStack.peek(1));
}

void ACC::OpGenerators::add(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& fn = assembly.fetchFunction();
    Location lhs = assembly.fetchLocation(op->lhs);
    Location rhs = assembly.fetchLocation(op->rhs);

    Location rax = Location::reg(Register::rax);
    Location rbx = Location::reg(Register::rbx);


    fn.createStructure(rax, "1", {lhs});
    fn.createStructure(rbx, "1", {rhs});
    fn.writeLine("add rax, rbx");

    Location result = Location::baseOffset(-(offset_t)fn.curBpOffset);
    fn.curBpOffset += 8;
    fn.requiredStackSize += 8;

    fn.createStructure(result, "1", {rax});
    assembly.emplaceLocation(op->result, result);
}

void ACC::OpGenerators::icopy(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& fn = assembly.fetchFunction();
    Location result = Location::baseOffset(-(offset_t)fn.curBpOffset);
    fn.curBpOffset += 8;
    fn.requiredStackSize += 8;


    Location lhs = Location::constant((unsigned char)op->lhs);

    fn.createStructure(result, "1", {lhs});
    assembly.emplaceLocation(op->result, result);

}

void ACC::OpGenerators::iSubtract(ACC::Operator *op, ACC::Assembly &assembly) {
    std::string lhs = std::to_string(op->lhs);
    std::string rhs = std::to_string(op->rhs);
    auto& targetFunction = assembly.fetchFunction();

    targetFunction.mov("rax", lhs);
    targetFunction.writeLine("sub rax, " + rhs);

    Location snippet = Location::baseOffset(targetFunction.curBpOffset);
    targetFunction.curBpOffset += 8;
    targetFunction.requiredStackSize += 8;


    Location store = Location::reg(Register::rax);

    targetFunction.createStructure(snippet, "1", {store});

    assembly.emplaceLocation(op->result, snippet);
}

void ACC::OpGenerators::subtract(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& fn = assembly.fetchFunction();
    Location lhs = assembly.fetchLocation(op->lhs);
    Location rhs = assembly.fetchLocation(op->rhs);

    Location rax = Location::reg(Register::rax);
    Location rbx = Location::reg(Register::rbx);


    fn.createStructure(rax, "1", {lhs});
    fn.createStructure(rbx, "1", {rhs});
    fn.writeLine("sub rax, rbx");

    Location result = Location::baseOffset(-(offset_t)fn.curBpOffset);
    fn.curBpOffset += 8;
    fn.requiredStackSize += 8;

    fn.createStructure(result, "1", {rax});
    assembly.emplaceLocation(op->result, result);
}

void ACC::OpGenerators::multiply(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& fn = assembly.fetchFunction();
    Location lhs = assembly.fetchLocation(op->lhs);
    Location rhs = assembly.fetchLocation(op->rhs);

    Location rax = Location::reg(Register::rax);
    Location rbx = Location::reg(Register::rbx);


    fn.createStructure(rax, "1", {lhs});
    fn.createStructure(rbx, "1", {rhs});
    fn.writeLine("imul rax, rbx");

    Location result = Location::baseOffset(-(offset_t)fn.curBpOffset);
    fn.curBpOffset += 8;
    fn.requiredStackSize += 8;

    fn.createStructure(result, "1", {rax});
    assembly.emplaceLocation(op->result, result);
}

void ACC::OpGenerators::imultiply(ACC::Operator *op, ACC::Assembly &assembly) {
    std::string lhs = std::to_string(op->lhs);
    std::string rhs = std::to_string(op->rhs);
    auto& targetFunction = assembly.fetchFunction();

    targetFunction.mov("rax", lhs);
    targetFunction.writeLine("imul rax, " + rhs);

    Location snippet = Location::baseOffset(targetFunction.curBpOffset);
    targetFunction.curBpOffset += 8;
    targetFunction.requiredStackSize += 8;
    Location store = Location::reg(Register::rax);

    targetFunction.createStructure(snippet, "1", {store});

    assembly.emplaceLocation(op->result, snippet);
}

void ACC::OpGenerators::idivide(ACC::Operator *op, ACC::Assembly &assembly) {
    std::string lhs = std::to_string(op->lhs);
    std::string rhs = std::to_string(op->rhs);
    auto& targetFunction = assembly.fetchFunction();

    targetFunction.mov("rax", lhs);
    targetFunction.writeLine("div rax, " + rhs);

    Location snippet = Location::baseOffset(targetFunction.curBpOffset);
    targetFunction.curBpOffset += 8;
    targetFunction.requiredStackSize += 8;

    Location store = Location::reg(Register::rax);

    targetFunction.createStructure(snippet, "1", {store});
    assembly.emplaceLocation(op->result, snippet);
}

void ACC::OpGenerators::divide(ACC::Operator *op, ACC::Assembly &assembly) {
    auto& fn = assembly.fetchFunction();
    Location lhs = assembly.fetchLocation(op->lhs);
    Location rhs = assembly.fetchLocation(op->rhs);

    Location rax = Location::reg(Register::rax);
    Location rbx = Location::reg(Register::rbx);


    fn.createStructure(rax, "1", {lhs});
    fn.createStructure(rbx, "1", {rhs});
    fn.writeLine("div rax, rbx");

    Location result = Location::baseOffset(-(offset_t)fn.curBpOffset);
    fn.curBpOffset += 8;
    fn.requiredStackSize += 8;

    fn.createStructure(result, "1", {rax});
    assembly.emplaceLocation(op->result, result);
}
