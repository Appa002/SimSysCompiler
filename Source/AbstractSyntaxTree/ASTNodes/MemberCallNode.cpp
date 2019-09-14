#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <Structure/Structures/Number/NumRValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Structure/Structures/Char/CharRValueStructure.h>
#include <Error/Errors.h>
#include <Structure/Structures/Bool/BoolRValueStructure.h>
#include <Structure/Structures/User/UserLValueStructure.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include <Structure/Structures/Bool/BoolLValueStructure.h>
#include <Structure/Structures/Char/CharLValueStructure.h>

#include "MemberCallNode.h"
#include "IdNode.h"
#include "TypeNode.h"

std::shared_ptr<ACC::Structure> ACC::MemberCallNode::generate(ACC::Code &code) {
    std::vector<ACC::Fn> overloads;

    auto thisArg = children[0]->generate(code);

    std::string id = "?" + thisArg->type.id + "." + traitName;

    try {
        overloads = code.getFnOverloads(id);
    } catch (errors::ASTError& err){
        err.lineContent = this->lineContent;
        err.lineNum = this->lineNum;
        throw;
    }

    auto &fn = code.getFnSymbol();

    size_t totalRspSubtracted = 0;

    auto asmAccessible = dynamic_cast<AsmAccessible*>(thisArg.get());
    auto thisArgAsPtr = std::make_shared<PtrRValueStructure>(asmAccessible->getAccess(), Type::createPtr(thisArg->type));

    std::vector<std::shared_ptr<Structure>> arguments;

    arguments.push_back(thisArgAsPtr);

    for (size_t i = 1; i < children.size(); i++) {
        auto value = children[i]->generate(code);
        arguments.push_back(value);

    }


    Fn callee;
    bool foundMatch = false;
    for (Fn &overload : overloads) {
        if (overload.argsType.size() != arguments.size())
            continue; // The possible overload takes a different number of arguments than provided.

        if (isPerfectMatch(arguments, overload)) {
            callee = overload;
            foundMatch = true;
            break; // A perfect match is always preferred,therefore we break.
        }

        if (isConvertable(arguments, overload)) {
            callee = overload;
            foundMatch = true;
            break;
        }

    }
    if (!foundMatch)
        throw errors::MissingOverload(this, id);
    // `callee` will now contain a COPY of the ACC::Fn object being called.


    if(callee.returnType.isComplex){
        // We can't return from the function simply by setting rdx. rdi will contain an address for where the returned
        // structure should go. The return node will place the structure there.

        fn.curBpOffset += callee.returnType.size;
        code.reserveRegister(Register::rDI);
        fn.writeLine("lea rdi, [rbp-"+ std::to_string(fn.curBpOffset) +"]");
    }

    for (long i = arguments.size() - 1; i >= 0; i--) {
        auto &value = arguments[i];

        std::shared_ptr<Structure> atRsp;

        if (value->type == Type("num", 8))
            atRsp = std::make_shared<NumLValueStructure>("rsp");

        else if (value->type == Type("char", 1))
            atRsp = std::make_shared<CharLValueStructure>("rsp");

        else if (value->type == Type("bool", 1))
            atRsp = std::make_shared<BoolLValueStructure>("rsp");

        else if (value->type.isPtr)
            atRsp = std::make_shared<PtrLValueStructure>("rsp", value->type);

        else
            atRsp = std::make_shared<UserLValueStructure>("rsp", value->type);

        fn.writeLine("sub rsp, " + std::to_string(value->type.size));
        totalRspSubtracted += value->type.size;

        try {
            atRsp->operatorCopy({value}, code);
        } catch (errors::ASTError &err) {
            err.lineNum = this->lineNum;
            err.lineContent = this->lineContent;
            throw;
        }


        value->cleanUp(code);
    }

    std::string name = callee.mangledName();

    fn.writeLine("call " + name);
    fn.writeLine("add rsp, " + std::to_string(totalRspSubtracted));

    Type returnType = callee.returnType;

    if (returnType == Type("num", 8))
        return std::make_shared<NumRValueStructure>(Register::rA);

    else if (returnType == Type("char", 1))
        return std::make_shared<CharRValueStructure>(Register::rA);

    else if (returnType == Type("bool", 1))
        return std::make_shared<BoolRValueStructure>(Register::rA);

    else if (returnType.isPtr)
        return std::make_shared<PtrRValueStructure>(Register::rA, returnType);


    else if (returnType.isComplex){
        code.freeRegister(Register::rDI);
        return std::make_shared<UserLValueStructure>("rbp - "+ std::to_string(fn.curBpOffset) ,returnType);
    }


    return nullptr;
}

ACC::MemberCallNode::MemberCallNode(ACC::AstOperator op, std::string const & traitName, std::vector<ACC::ASTNode *> children)
: ASTNode(op, std::move(children)), traitName(traitName) {

}

std::vector<ACC::Type> ACC::MemberCallNode::getArgumentTypes() {
    std::vector<Type> out;
    for (size_t i = 1; i < children.size(); i++) {
        out.push_back(dynamic_cast<TypeNode*>(children[i])->getType());
    }
    return out;
}

bool ACC::MemberCallNode::isPerfectMatch(std::vector<std::shared_ptr<Structure>> values, Fn &overload) {
    // A possible overload is a perfect match, if all argument types fit without conversion operations.
    bool ok = true;
    for (size_t i = 0; i < overload.argsType.size(); i++) {
        if (values[i]->type != overload.argsType[i]) {
            ok = false;
            break;
        }
    }

    return ok;
}

bool ACC::MemberCallNode::isConvertable(std::vector<std::shared_ptr<Structure>> values, Fn &overload) {
    for (size_t i = 0; i < values.size(); i++) {
        if(!values[i]->hasConversionTo(overload.argsType[i]))
            return false;
    }
    return true;
}

std::string ACC::MemberCallNode::createRepresentation() const {
    return "Member Call ( "+traitName+" )";
}
