#include "PtrLValueStructure.h"
#include "PtrRValueStructure.h"

#include <utility>
#include <Assembly/Code.h>
#include <General/builtinTypes.h>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <Error/Errors.h>
#include <Structure/RegisterAccessible.h>
#include <Structure/ImmediatAccessible.h>


ACC::PtrLValueStructure::PtrLValueStructure(std::string access, ACC::Type type)
        : PtrStructure(ValueCategory::lvalue, type), access(std::move(access)) {

}

void ACC::PtrLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto &fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(8, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::PtrLValueStructure::operatorCopy(std::vector<std::shared_ptr<Structure>> objList, ACC::Code &code) {
   auto & obj = objList[0];
    if(!obj->type.isPtr)
        obj = obj->operatorPtr(code, this->type);

    if (obj->vCategory == ValueCategory::lvalue) {
        auto *objAsL = dynamic_cast<AsmAccessible *>(obj.get());
        auto &fn = code.getFnSymbol();
        Register reg = code.getFreeRegister();
        std::string regStr = registerToString(8, reg);

        fn.writeLine("mov " + regStr + ", [" + objAsL->getAccess() + "]");
        fn.writeLine("mov [ " + access + " ], " + regStr);
        code.freeRegister(reg);
    } else if (obj->vCategory == ValueCategory::rvalue){
        auto *objAsR = dynamic_cast<RegisterAccessible*>(obj.get());
        auto &fn = code.getFnSymbol();
        Register r;

        if(obj->type.isPtr){
            auto* objAsPtr = dynamic_cast<PtrRValueStructure*>(obj.get());

            if(!objAsPtr->access.empty()){
                r = code.getFreeRegister();
                fn.writeLine("lea " + registerToString(8, r) + ", [" + objAsPtr->access + "]");
                code.freeRegister(r);
            }else{
                r = objAsPtr->reg;
            }
        }else{
            r = objAsR->getRegister();
        }

        fn.writeLine("mov [ " + access + " ], " + registerToString(8, r));
    } else if (obj->vCategory == ValueCategory::ivalue){
        auto *objAsI = dynamic_cast<ImmediatAccessible*>(obj.get());
        auto &fn = code.getFnSymbol();
        if(obj->type.size == 8)
            fn.writeLine("mov qword [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 4)
            fn.writeLine("mov dword [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 2)
            fn.writeLine("mov word [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 1)
            fn.writeLine("mov byte [ " + access + " ], " + objAsI->getValue());
    }
    return nullptr;
}

std::string const &ACC::PtrLValueStructure::getAccess() const {
    return access;
}

std::shared_ptr<ACC::Structure> ACC::PtrLValueStructure::operatorChar(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "char");
}

std::shared_ptr<ACC::Structure> ACC::PtrLValueStructure::operatorNum(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "num");
}

std::shared_ptr<ACC::Structure> ACC::PtrLValueStructure::operatorBool(ACC::Code &code) {
    throw errors::TypeConversion(nullptr, "ptr", "bool");
}

std::shared_ptr<ACC::Structure> ACC::PtrLValueStructure::operatorPtr(ACC::Code &code, ACC::Type pointingTo) {
    return std::make_shared<PtrLValueStructure>(access, pointingTo);
}

bool ACC::PtrLValueStructure::hasConversionTo(const ACC::Type &id) {
    return id.isPtr;
}
