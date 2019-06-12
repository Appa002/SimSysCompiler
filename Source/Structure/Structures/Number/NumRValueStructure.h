//
// Created by a_mod on 07.06.2019.
//

#ifndef SIMSYSCOMPILER_NUMOPERATORRVALUE_H
#define SIMSYSCOMPILER_NUMOPERATORRVALUE_H

#include <Structure/Structure.h>
#include "Structure/Structures/ElementaryStructure.h"
#include <Structure/Structures/Number/NumStructure.h>
#include <Structure/RegisterAccessible.h>

namespace ACC {
    class NumRValueStructure : public NumStructure, public RegisterAccessible {
    private:
        Register reg;
    public:
        explicit NumRValueStructure(Register reg);

        void loadToRegister(Register reg, Code& code) override;
        Register getRegister() const override;

        std::shared_ptr<ACC::Structure> operatorCopy(std::shared_ptr<Structure> address, ACC::Code &code) override;
        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;
    };
}

#endif //SIMSYSCOMPILER_NUMOPERATORRVALUE_H
