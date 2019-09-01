#include <utility>

//
// Created by a_mod on 07.06.2019.
//

#include <Assembly/Code.h>
#include <Structure/Structures/Char/CharRValueStructure.h>
#include <Structure/Structures/Bool/BoolRValueStructure.h>
#include <Structure/Structures/Number/NumRValueStructure.h>
#include <Structure/Structures/Pointer/PtrRValueStructure.h>
#include <Structure/Structures/Char/CharLValueStructure.h>
#include <Structure/Structures/Number/NumLValueStructure.h>
#include <Structure/Structures/Bool/BoolLValueStructure.h>
#include <Structure/Structures/Pointer/PtrLValueStructure.h>
#include <Structure/ImmediatAccessible.h>
#include "GenericLValueStructure.h"

ACC::GenericLValueStructure::GenericLValueStructure(ACC::Type type, std::string access)
: ElementaryStructure(ValueCategory::lvalue, type), access(std::move(access))
{

}

void ACC::GenericLValueStructure::loadToRegister(ACC::Register reg, ACC::Code &code) {
    auto& fn = code.getFnSymbol();
    fn.writeLine("mov " + registerToString(type.size, reg) + ", [" + access + "]");
}

std::shared_ptr<ACC::Structure>
ACC::GenericLValueStructure::operatorCopy(std::shared_ptr<ACC::Structure> obj, ACC::Code & code) {
    if(obj->vCategory == ValueCategory::lvalue) {
        auto &fn = code.getFnSymbol();
        auto *objAsL = dynamic_cast<AsmAccessible *>(obj.get());


        if(obj->type.size <= 8) {
            Register reg = code.getFreeRegister();
            std::string regStr = registerToString(type.size, reg);

            fn.writeLine("mov " + regStr + ", [" + objAsL->getAccess() + "]");
            fn.writeLine("mov [ " + access + " ], " + regStr);
            code.freeRegister(reg);
        } else{
            // The type can't be moved using a single register like above as it is larger then a qword.

            Register reg = code.getFreeRegister();
            std::string regStr = registerToString(type.size, reg);

            long bytesLeftToMove = obj->type.size;

            while(bytesLeftToMove > 0){

                if (bytesLeftToMove >= 8) {
                    std::string offset = "+" + std::to_string(obj->type.size - bytesLeftToMove);

                    fn.writeLine("mov qword " + regStr + ", [" + objAsL->getAccess() + offset + "]");
                    fn.writeLine("mov qword [ " + access + offset + " ], " + regStr);
                    bytesLeftToMove -= 8;
                } else{
                    std::string offset = "+" + std::to_string(obj->type.size - bytesLeftToMove);

                    if(bytesLeftToMove == 1){
                        fn.writeLine("mov byte " + regStr + ", [" + objAsL->getAccess() + offset + "]");
                        fn.writeLine("mov byte [ " + access + offset + " ], " + regStr);
                        bytesLeftToMove -= 1;

                    } else if(bytesLeftToMove == 2){
                        fn.writeLine("mov word " + regStr + ", [" + objAsL->getAccess() +  offset + "]");
                        fn.writeLine("mov word [ " + access +  offset + " ], " + regStr);
                        bytesLeftToMove -= 2;

                    } else if(bytesLeftToMove >= 3){
                        fn.writeLine("mov dword " + regStr + ", [" + objAsL->getAccess() + offset + "]");
                        fn.writeLine("mov dword [ " + access +  offset + " ], " + regStr);
                        bytesLeftToMove -= 4;
                    }
                }
            }

            code.freeRegister(reg);

        }

        return obj;

    } else if(obj->vCategory == ValueCategory::rvalue) {
        auto &fn = code.getFnSymbol();
        auto *objAsR = dynamic_cast<RegisterAccessible *>(obj.get());

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

        fn.writeLine("mov [ " + access + " ], " + registerToString(obj->type.size, r));

        return obj;

    } else if(obj->vCategory == ValueCategory::ivalue) {
        auto &fn = code.getFnSymbol();
        auto *objAsI = dynamic_cast<ImmediatAccessible *>(obj.get());

        if(obj->type.size == 8)
            fn.writeLine("mov qword [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 4)
            fn.writeLine("mov dword [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size >= 2)
            fn.writeLine("mov word [ " + access + " ], " + objAsI->getValue());
        else if(obj->type.size == 1)
            fn.writeLine("mov byte [ " + access + " ], " + objAsI->getValue());


            return obj;
    }
    return nullptr;
}

std::string const &ACC::GenericLValueStructure::getAccess() const {
    return access;
}

std::shared_ptr<ACC::Structure> ACC::GenericLValueStructure::operatorChar(ACC::Code &code) {
    return std::make_shared<CharLValueStructure>(access);
}

std::shared_ptr<ACC::Structure> ACC::GenericLValueStructure::operatorNum(ACC::Code &code) {
    return std::make_shared<NumLValueStructure>(access);
}

std::shared_ptr<ACC::Structure> ACC::GenericLValueStructure::operatorBool(ACC::Code &code) {
    return std::make_shared<BoolLValueStructure>(access);
}

std::shared_ptr<ACC::Structure> ACC::GenericLValueStructure::operatorPtr(Code &code, Type pointingTo) {
    return std::make_shared<PtrLValueStructure>(access, pointingTo);

}

