#include <utility>

#include "ReturnNode.h"

std::shared_ptr<ACC::Structure> ACC::ReturnNode::generate(ACC::Code &code) {
  /*  auto returnValue = node->children[0]->asExpr()->generate(code);
    auto& fn = code.getFnSymbol();

    fn.writeLine("add rsp, " + std::to_string(fn.curBpOffset));
    if(returnValue.type == StructureType::elementary){
        fn.writeLine(returnValue.copyToRegister("rax", code));
    }
    else{} // TODO: Implement.

    fn.writeLine("pop rbp");
    fn.writeLine("ret");
*/
    return nullptr;
}

ACC::ReturnNode::ReturnNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}
