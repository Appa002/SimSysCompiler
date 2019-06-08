//
// Created by a_mod on 07.06.2019.
//

#ifndef SIMSYSCOMPILER_PTRRVALUE_H
#define SIMSYSCOMPILER_PTRRVALUE_H

#include <Structure/Structures/GenericLValueStructure.h>
#include "PtrStructure.h"

namespace ACC {
    class PtrRValueStructure : public PtrStructure {
    public:
        std::string access;

        explicit PtrRValueStructure(std::string access, Type type);

        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> other, Code &code) override;

        void loadToRegister(Register reg, Code& code) override;

    };
}

#endif //SIMSYSCOMPILER_PTRRVALUE_H
