#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <Structure/Structures/Number/NumRValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Structure/Structures/Char/CharRValueStructure.h>

#include "CallNode.h"

std::shared_ptr<ACC::Structure> ACC::CallNode::generate(ACC::Code &code) {
    auto& overloads = code.getFnOverloads(children[0]->data.asT<std::string>());
    auto& fn = code.getFnSymbol();
    Fn callee;

    bool foundMatch = false;

    for (Fn& overload : overloads) {
        if (overload.argsType.size() != children.size() - 1)
            continue; // The possible overload takes a different number of arguments than provided.

        if (isPerfectMatch(overload)){
            callee = overload;
            foundMatch = true;
            break; // A perfect match is always preferred,therefore we break.
        }

        if(isConvertable(overload)){
            callee = overload;
            foundMatch = true;
            break;
        }

    }
    if(!foundMatch)
        throw std::runtime_error("No fitting overload for function call to `"+children[0]->data.asT<std::string>()+"`");
    // `callee` will now contain a COPY of the ACC::Fn object being called.


    auto argumentTypes = getArgumentTypes();
    size_t totalRspSubtracted = 0;

    for(size_t i = children.size() - 1; i >= 1; i--){
        auto value = children[i]->generate(code);

        if(callee.argsType[i-1] != value->type){
            // We need to do argument conversion
            if(callee.argsType[i-1] == BuiltIns::charType)
                value = value->operatorChar(code);
            else if(callee.argsType[i-1] == BuiltIns::numType)
                value = value->operatorNum(code);
            else if(callee.argsType[i-1] == BuiltIns::boolType)
                value = value->operatorBool(code);
            else if(callee.argsType[i-1] == BuiltIns::ptrType)
                value = value->operatorPtr(code, Type(callee.argsType[i-1].getPointingTo()));
            else
                throw std::runtime_error("Unknown Type");
        }

        fn.writeLine("sub rsp, " + std::to_string(value->type.getSize()));
        totalRspSubtracted += value->type.getSize();

        value->operatorCopy(std::make_shared<GenericLValueStructure>(value->type, "rsp"), code);
        value->cleanUp(code);

        argumentTypes.push_back(value->type);
    }

    std::string name = callee.mangledName();

    fn.writeLine("call " + name);
    fn.writeLine("add rsp, " + std::to_string(totalRspSubtracted));

    Type returnType = callee.returnType;

    if(returnType == Type(BuiltIns::numType))
        return std::make_shared<NumRValueStructure>(Register::rA);

    else if (returnType == Type(BuiltIns::ptrType))
        return std::make_shared<PtrRValueStructure>(Register::rA, Type(type.getPointingTo()));

    else if (returnType == Type(BuiltIns::charType))
        return std::make_shared<CharRValueStructure>(Register::rA);

    return nullptr;
}

ACC::CallNode::CallNode(ACC::AstOperator op, std::vector<ACC::ASTNode *> children) : ASTNode(op, std::move(children)) {

}

std::vector<ACC::Type> ACC::CallNode::getArgumentTypes() {
    std::vector<Type> out;
    for(size_t i = 1; i < children.size(); i++){
        out.push_back(children[i]->type);
    }
    return out;
}

bool ACC::CallNode::isPerfectMatch(Fn& fn) {
    // A possible overload is a perfect match, if all argument types fit without conversion operations.
    bool ok = true;
    for(size_t i = 0; i < fn.argsType.size(); i++){
        auto providedType = children[i+1]->type;
        if(providedType != fn.argsType[i]){
            ok = false;
            break;
        }
    }

    return ok;
}

bool ACC::CallNode::isConvertable(ACC::Fn &overload) {
    // As the ability to convert a function is dependent on the value category of the structure and that cannot be
    // determent at this time, this function may say a overload is convertable even though it is not.
    bool ok = true;
    for (size_t i = 0; i < overload.argsType.size(); i++){
        auto providedType = children[i+1]->type;
        bool canBeConverted = false;
        for (TypeId conversion : providedType.getTypeId().convertableTo){
            if(conversion == overload.argsType[i].getTypeId())
                canBeConverted = true;
        }
        if(!canBeConverted){
            ok = false;
            break;
        }
        canBeConverted = false;
    }
    return ok;
}
