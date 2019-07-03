#include <utility>
#include <Structure/Structures/ElementaryStructure.h>

#include "ReturnNode.h"

std::shared_ptr<ACC::Structure> ACC::ReturnNode::generate(ACC::Code &code) {
    auto returnValue = children[0]->generate(code);
    auto &fn = code.getFnSymbol();

    auto* asElem = dynamic_cast<ElementaryStructure*>(returnValue.get());
    if(asElem)
        asElem->loadToRegister(Register::rA, code);
    else
        ; //TODO: Figure out what to do for none elementary types....
        /*
         * TODO:
         * Apparently the caller puts the address of where the complex object(returning object) is going to be stored
         * on his stack into rdi. The callee then uses this address to create the complex object at rdi.
         * e.g.: (ASM)
         * caller:
         * sub rsp 24 ; 24 size of complex object
         * lea rdi [rsp] ; address of complex object
         * call callee
         * ...
         *
         * callee:
         * enter
         *
         * mov [rdi], 90 ; initialises complex object
         * mov [rdi-8], 91 ;
         * .....
         * leave
         * ret
         *
         * */

    returnValue->cleanUp(code);

   /* fn.writeLine("add rsp, " + std::to_string(fn.curBpOffset));
    fn.writeLine("pop rbp");
    fn.writeLine("ret");*/

   /* TODO: Figure out how `leave` magically cleans up the stack when using buffers with variable sizes
    * TODO:, even though such doesn't seem to be immediately doable using the method above.*/

    fn.writeLine("leave");
    fn.writeLine("ret");
    return nullptr;
}

ACC::ReturnNode::ReturnNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op,
                                                                                                 std::move(children)) {

}
