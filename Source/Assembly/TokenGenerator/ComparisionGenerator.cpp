#include <builtinTypes.h>
#include "ComparisionGenerator.h"

ACC::ComparisionGenerator::ComparisionGenerator(ACC::ASTNode *node) : Expr(node) {
    cmpType = StructureFlags::EQ;
}

ACC::Structure ACC::ComparisionGenerator::generate(ACC::Code &code) {
    auto lhs = node->children[0]->asExpr()->generate(code);
    auto rhs = node->children[1]->asExpr()->generate(code);
    auto& fn = code.getFnSymbol();


    auto lhsRegister = code.getFreeRegister();
    auto rhsRegister = code.getFreeRegister();

    if(lhs.type == StructureType::elementary){
        fn.writeLine(lhs.copyToRegister(registerToString(8, lhsRegister), code));
    }

    if(rhs.type == StructureType::elementary){
        fn.writeLine(rhs.copyToRegister(registerToString(8, rhsRegister), code));
    }

    fn.writeLine("cmp "+ registerToString(8, lhsRegister) +", "+ registerToString(8, rhsRegister));

    auto return_struct = Structure(StructureType::elementary);
    return_struct.typeId = BuiltIns::boolType;
    //TODO: Type Conversions.

    return_struct.flag = cmpType;

    code.freeRegister(lhsRegister);
    code.freeRegister(rhsRegister);
    code.freeRegister(lhs.registerUsed);
    code.freeRegister(rhs.registerUsed);
    return return_struct;
}

ACC::ComparisionGenerator::ComparisionGenerator(ACC::ASTNode *node, ACC::StructureFlags cmpType) : Expr(node) {
    this->cmpType = cmpType;
}
