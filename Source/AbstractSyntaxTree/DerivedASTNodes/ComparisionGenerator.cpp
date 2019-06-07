#include <builtinTypes.h>
#include "ComparisionGenerator.h"


ACC::Structure* ACC::ComparisionGenerator::generate(ACC::Code &code) {
/*    auto lhs = node->children[0]->asExpr()->generate(code);
    auto rhs = node->children[1]->asExpr()->generate(code);
    auto& fn = code.getFnSymbol();


    Register lhsRegister;
    Register rhsRegister;
    if(!lhs.registerUsed.empty())
        lhsRegister = lhs.registerUsed[0];
    else
        lhsRegister = code.getFreeRegister();


    if(!rhs.registerUsed.empty())
        rhsRegister = rhs.registerUsed[0];
    else
        rhsRegister = code.getFreeRegister();

    if(lhs.type == StructureType::elementary){
        fn.writeLine(lhs.copyToRegister(registerToString(8, lhsRegister), code));
    }

    if(rhs.type == StructureType::elementary){
        fn.writeLine(rhs.copyToRegister(registerToString(8, rhsRegister), code));
    }

    fn.writeLine("cmp "+ registerToString(8, lhsRegister) +", "+ registerToString(8, rhsRegister));

    auto return_struct = Structure(StructureType::elementary);
    return_struct.typeId = BuiltIns::boolType;
    return_struct.isStored = false;
    //TODO: Type Conversions.

    return_struct.registerUsed = {lhsRegister};

    switch (cmpType){
        case ComparisionType::EQ:
            fn.writeLine("sete " + registerToString(1, lhsRegister));
            break;
        case ComparisionType::LT:
            fn.writeLine("setl " + registerToString(1, lhsRegister));
            break;
        case ComparisionType::GT:
            fn.writeLine("setg " + registerToString(1, lhsRegister));
            break;
        case ComparisionType::NEQ:
            fn.writeLine("setne " + registerToString(1, lhsRegister));
            break;
        case ComparisionType::LET:
            fn.writeLine("setle " + registerToString(1, lhsRegister));
            break;
        case ComparisionType::GET:
            fn.writeLine("setge " + registerToString(1, lhsRegister));
            break;
    }

    return_struct.copyToRegister = [=](std::string reg, Code& c){
        if(reg != registerToString(1, lhsRegister))
            return "movzx " + reg + ", " + registerToString(1, lhsRegister);
        return std::string();
    };

    return_struct.copyToStack = [=](Code& c){
        return "mov byte [rsp], " + registerToString(1, lhsRegister);
    };

    return_struct.copyToBpOffset = [=](int32_t offset, Code& c){
        std::string sign = offset < 0 ? ("-") : ("+");
        offset = offset < 0 ? (-offset) : (offset);
        return "mov byte [rbp "+sign+std::to_string(offset)+"], " + registerToString(1, lhsRegister);
    };

    code.freeRegister(rhsRegister);
    code.freeRegister(lhs.registerUsed);
    code.freeRegister(rhs.registerUsed);
    return return_struct;
    */
    return nullptr;
}

