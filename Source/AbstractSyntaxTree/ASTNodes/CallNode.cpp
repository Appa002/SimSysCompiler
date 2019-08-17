#include <utility>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <Structure/Structures/Number/NumRValueStructure.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Structure/Structures/Char/CharRValueStructure.h>
#include <Error/Errors.h>

#include "CallNode.h"

std::shared_ptr<ACC::Structure> ACC::CallNode::generate(ACC::Code &code) {
    std::vector<ACC::Fn> overloads;

    try {
        overloads = code.getFnOverloads(children[0]->data.asT<std::string>());
    } catch (errors::ASTError& err){
        err.lineContent = this->lineContent;
        err.lineNum = this->lineNum;
        throw;
    }

    auto &fn = code.getFnSymbol();

    size_t totalRspSubtracted = 0;

    std::vector<std::shared_ptr<Structure>> arguments;

    for (size_t i = 1; i < children.size(); i++) {
        auto value = children[i]->generate(code);
        arguments.push_back(value);

    }


    Fn callee;
    bool foundMatch = false;
    for (Fn &overload : overloads) {
        if (overload.argsType.size() != children.size() - 1)
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
        throw errors::MissingOverload(this, children[0]->data.asT<std::string>());
    // `callee` will now contain a COPY of the ACC::Fn object being called.


    for (long i = arguments.size() - 1; i >= 0; i--) {
        auto &value = arguments[i];
        if (callee.argsType[i] != value->type) {
            // We need to do argument conversion
            if (callee.argsType[i] == BuiltIns::charType) {
                try {
                    value = value->operatorChar(code);
                } catch (errors::ASTError &err) {
                    err.lineNum = this->lineNum;
                    err.lineContent = this->lineContent;
                    throw;
                }
            } else if (callee.argsType[i] == BuiltIns::numType) {
                try {
                    value = value->operatorNum(code);
                } catch (errors::ASTError &err) {
                    err.lineNum = this->lineNum;
                    err.lineContent = this->lineContent;
                    throw;
                }
            } else if (callee.argsType[i] == BuiltIns::boolType) {
                try {
                    value = value->operatorBool(code);
                } catch (errors::ASTError &err) {
                    err.lineNum = this->lineNum;
                    err.lineContent = this->lineContent;
                    throw;
                }
            } else if (callee.argsType[i] == BuiltIns::ptrType) {
                try {
                    value = value->operatorPtr(code, Type(callee.argsType[i].getPointingTo()));
                } catch (errors::ASTError &err) {
                    err.lineNum = this->lineNum;
                    err.lineContent = this->lineContent;
                    throw;
                }
            } else
                throw errors::UnknownType(this, "NEED NEW TYPE SYSTEM"); // TODO: Implement
        }

        fn.writeLine("sub rsp, " + std::to_string(value->type.getSize()));
        totalRspSubtracted += value->type.getSize();

        try {
            value->operatorCopy(std::make_shared<GenericLValueStructure>(value->type, "rsp"), code);
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

    if (returnType == Type(BuiltIns::numType))
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
    for (size_t i = 1; i < children.size(); i++) {
        out.push_back(children[i]->type);
    }
    return out;
}

bool ACC::CallNode::isPerfectMatch(std::vector<std::shared_ptr<Structure>> values, Fn &overload) {
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

bool ACC::CallNode::isConvertable(std::vector<std::shared_ptr<Structure>> values, Fn &overload) {
    bool ok = true;
    for (size_t i = 0; i < values.size(); i++) {
        bool canBeConverted = false;
        for (const TypeId &conversion : values[i]->type.getTypeId().convertableTo) {
            if (conversion == overload.argsType[i].getTypeId())
                canBeConverted = true;
        }
        if (!canBeConverted) {
            ok = false;
            break;
        }
    }
    return ok;
}
