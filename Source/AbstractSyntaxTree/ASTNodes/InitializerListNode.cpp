#include <utility>

#include "InitializerListNode.h"
#include <Logger/Logger.h>
#include <Error/ASTError.h>

std::shared_ptr<ACC::Structure> ACC::InitializerListNode::generate(ACC::Code &code) {
    throw std::runtime_error("Can't generate on an initializer list node");
    return nullptr;
}

ACC::InitializerListNode::InitializerListNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}

std::vector<std::shared_ptr<ACC::Structure>> ACC::InitializerListNode::unpack(ACC::Code &code) {
    std::vector<std::shared_ptr<ACC::Structure>> out;
    for(auto const & child : children){
        out.push_back(child->generate(code));
    }

    return out;

}

std::string ACC::InitializerListNode::createRepresentation() const {
    return "initializer_list";
}
