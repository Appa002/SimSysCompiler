#include <utility>
#include <Error/ASTError.h>

#include "ForNode.h"


std::shared_ptr<ACC::Structure> ACC::ForNode::generate(ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    auto top = code.getUUID();
    auto rest = code.getUUID();


    code.pushScope();

    auto index = children[0]->generate(code);
    auto limit = children[1]->generate(code);

    fn.writeLine("." + top + ":");


    try {
        index->operatorForDone(limit, code);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }


    // At this point rflags has been set according to the comparison of index and limit

    fn.writeLine("jne ." + rest);
    children[2]->generate(code);


    // Iterating
    try {
        index->operatorForNext(code);
    } catch (errors::ASTError& err){
        err.lineNum = this->lineNum;
        err.lineContent = this->lineContent;
        throw;
    }
    code.popScope();

    // Looping back up / seting up rest..
    fn.writeLine("jmp ." + top);
    fn.writeLine("."+rest+":");


    index->cleanUp(code);
    limit->cleanUp(code);

    return nullptr;
}


ACC::ForNode::ForNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}

