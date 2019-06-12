//
// Created by a_mod on 07.06.2019.
//

#ifndef SIMSYSCOMPILER_PTRRVALUE_H
#define SIMSYSCOMPILER_PTRRVALUE_H

#include <Structure/Structures/GenericLValueStructure.h>
#include <Structure/RegisterAccessible.h>
#include "PtrStructure.h"

namespace ACC {
    class PtrRValueStructure : public PtrStructure, public RegisterAccessible {
    public:
        Register reg;
        std::string access;

        PtrRValueStructure(Register reg, Type type);
        PtrRValueStructure(std::string access, Type type);

        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> other, Code &code) override;

        void loadToRegister(Register reg, Code& code) override;
        Register getRegister() const override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;

    };
}

#endif //SIMSYSCOMPILER_PTRRVALUE_H
