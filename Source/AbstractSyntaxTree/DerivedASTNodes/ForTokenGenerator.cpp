#include "ForTokenGenerator.h"

ACC::Register getEfficientRegister(ACC::Structure structure, ACC::Code& code){
/*    ACC::Register reg;
    if(!structure.registerUsed.empty())
        reg = structure.registerUsed[0];
    else
        reg = code.getFreeRegister();
    return reg;
*/
}

ACC::Structure* ACC::ForTokenGenerator::generate(ACC::Code &code) {
    /* Assume:
     * for index -> limit:
     *      ...block
     * ...rest
     * */
    /*

    auto& fn = code.getFnSymbol();
    auto top = code.getUUID();
    auto rest = code.getUUID();

    fn.writeLine("." + top + ":");

    Structure limit = node->children[1]->asExpr()->generate(code);
    Register rhs = getEfficientRegister(limit, code);
    fn.writeLine(limit.copyToRegister(registerToString(limit.typeId.getSize(), rhs), code));


    Structure index = node->children[0]->asExpr()->generate(code);
    Register lhs = getEfficientRegister(index, code);
    fn.writeLine(index.copyToRegister(registerToString(index.typeId.getSize(), lhs), code));

    fn.writeLine("cmp "+ registerToString(index.typeId.getSize(), lhs) +", "+ registerToString(limit.typeId.getSize(), rhs));

    code.freeRegister(lhs);
    code.freeRegister(rhs);
    code.freeRegister(limit.registerUsed);
    code.freeRegister(index.registerUsed);

    // At this point rflags has been set according to the comparison of index and limit

    fn.writeLine("jge ." + rest);
    code.pushScope();
    Structure body = node->children[2]->asExpr()->generate(code);
    code.popScope();
    code.freeRegister(body.registerUsed);

     Adding one to the index
    handleAddition(fn, code, index);

     Looping back up / seting up rest..
    fn.writeLine("jmp ." + top);
    fn.writeLine("."+rest+":");*/


    return {};
}

void ACC::ForTokenGenerator::handleAddition(ACC::Fn &fn, ACC::Code &code, ACC::Structure index) {
   /*
    Register valueReg = code.getFreeRegister();
    Register addressReg = code.getFreeRegister();

    fn.writeLine(index.copyToRegister(registerToString(index.typeId.getSize(), valueReg), code));
    fn.writeLine("add " + registerToString(index.typeId.getSize(), valueReg) + ", 1");

    fn.writeLine(index.copyAddrToRegister(registerToString(8, addressReg), code));
    fn.writeLine("mov [" + registerToString(8, addressReg) + "], " + registerToString(index.typeId.getSize(), valueReg));
    code.freeRegister({valueReg, addressReg});*/

}

