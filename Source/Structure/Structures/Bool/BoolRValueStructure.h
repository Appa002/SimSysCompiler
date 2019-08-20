//
// Created by a_mod on 07.06.2019.
//

#ifndef SIMSYSCOMPILER_BOOLRVALUESTRUCTURE_H
#define SIMSYSCOMPILER_BOOLRVALUESTRUCTURE_H

#include <Structure/RegisterAccessible.h>
#include "Structure/Structures/ElementaryStructure.h"
#include "BoolStructure.h"

namespace ACC {
    class BoolRValueStructure : public BoolStructure, public RegisterAccessible{
    public:
        Register reg;

        explicit BoolRValueStructure(Register reg);
        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;

        void loadToRegister(Register reg, Code& code) override;

        Register getRegister() const override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;

        bool hasConversionTo(const Type &id) override;


    };
}

#endif //SIMSYSCOMPILER_BOOLRVALUESTRUCTURE_H
