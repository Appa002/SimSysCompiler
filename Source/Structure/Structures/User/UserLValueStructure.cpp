//
// Created by a_mod on 01.09.2019.
//

#include "UserLValueStructure.h"
#include <Assembly/Code.h>
#include <Error/Errors.h>
#include <utility>
#include <Structure/RegisterAccessible.h>
#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/Structures/Number/NumRValueStructure.h>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <Structure/Structures/Char/CharRValueStructure.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include <Types/TypeTable.h>

ACC::UserLValueStructure::UserLValueStructure(std::string access, const Type &type)
        : access(std::move(access)), UserStructure(ValueCategory::lvalue, type) {

}

std::string const &ACC::UserLValueStructure::getAccess() const {
    return access;
}

std::shared_ptr<ACC::Structure>
ACC::UserLValueStructure::operatorCopy(std::shared_ptr<Structure> obj, ACC::Code &code) {

    if (obj->type == type
    && !code.hasOverload(
            "?" + type.id + ".operatorCopy",
            Type("num", 8),
            {Type::createPtr(type), obj->type})) {

        auto &fn = code.getFnSymbol();
        auto byteWiseCopyFn = code.getFnOverloads("?byteWiseCopy")[0];


        fn.writeLine("sub rsp, 8");
        fn.writeLine("mov qword [rsp], " + std::to_string(obj->type.size));

        auto asmAccessible = dynamic_cast<AsmAccessible*>(obj.get());

        fn.writeLine("sub rsp, 8");
        Register ptr = code.getFreeRegister();
        fn.writeLine("lea " + registerToString(8, ptr) + ", [" + asmAccessible->getAccess() + "]");
        fn.writeLine("mov [rsp], " + registerToString(8, ptr));
        code.freeRegister(ptr);

        Register r = code.getFreeRegister();
        fn.writeLine("sub rsp, 8");
        fn.writeLine("lea "+registerToString(8, r)+", [" + access + "]");
        fn.writeLine("mov [rsp], " + registerToString(8, r));
        code.freeRegister(r);

        fn.writeLine("call " + byteWiseCopyFn.mangledName()); //Move size and address

        return nullptr;

    }
    std::vector<Fn> overloads;
    try {
        overloads = code.getFnOverloads("?" + type.id + ".operatorCopy");
    }
    catch (errors::MissingOverload &) {
        std::string typeRep;
        if (obj->type.isPtr) {
            typeRep = "ptr<" + obj->type.id + ">";
        } else {
            typeRep = obj->type.id;
        }

        throw errors::UnimplementedFunction(nullptr, type.id, "operatorCopy(" + typeRep + ")");
    }

    auto &fn = code.getFnSymbol();

    for (auto const &overload : overloads) {
        if (overload.argsType.size() == 2 && overload.argsType[1] == obj->type) {

            fn.writeLine("sub rsp, 8");
            std::make_shared<GenericLValueStructure>(obj->type, "rsp")->operatorCopy(obj, code);


            Register r = code.getFreeRegister();
            fn.writeLine("sub rsp, 8");
            fn.writeLine("lea "+registerToString(8, r)+", [" + access + "]");
            fn.writeLine("mov [rsp], " + registerToString(8, r));
            code.freeRegister(r);


            fn.writeLine("call " + overload.mangledName());
            return obj;

        }
    }

    throw errors::MissingOverload(nullptr, "operatorCopy(" + obj->type.id + ") for `" + type.id + "`");

}

std::shared_ptr<ACC::Structure> ACC::UserLValueStructure::operatorDot(ACC::Code &code, std::string member) {
    auto& fn = code.getFnSymbol();

    if(type.fieldSizes.find(member) == type.fieldSizes.cend())
        throw errors::UnknownMember(nullptr, type.id, member);

    size_t offset = type.fieldSizes[member];


    if(type.fields[member].typeName == "char"){

        auto out = std::make_shared<CharLValueStructure>(this->access + " + " + std::to_string(offset));
        return out;

    } else if(type.fields[member].typeName == "num"){
        auto out = std::make_shared<NumLValueStructure>(this->access + " + " + std::to_string(offset));
        return out;

    }  else if(type.fields[member].isPtr ){

        auto ptrType = TypeTable::get()->getType(type.fields[member].typeName);

        auto out = std::make_shared<PtrLValueStructure>(this->access + " + " + std::to_string(offset), ptrType);

        return out;

    } else {
        auto memberType = TypeTable::get()->getType(type.fields[member].typeName);

        auto out = std::make_shared<UserLValueStructure>(this->access + " + " + std::to_string(offset), memberType);

        return out;
    }


}
