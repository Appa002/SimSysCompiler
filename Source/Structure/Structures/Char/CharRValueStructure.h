//
// Created by a_mod on 08.06.2019.
//

#ifndef SIMSYSCOMPILER_CHARRVALUESTRUCTURE_H
#define SIMSYSCOMPILER_CHARRVALUESTRUCTURE_H

#include <Structure/RegisterAccessible.h>
#include "CharStructure.h"

namespace ACC {
    class CharRValueStructure : public CharStructure, public RegisterAccessible{
    private:
        Register reg;
    public:
        explicit CharRValueStructure(Register reg);

        void loadToRegister(Register reg, Code& code) override;

        std::shared_ptr<ACC::Structure> operatorCopy(std::shared_ptr<Structure> address, ACC::Code &code) override;

        Register getRegister() const override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;
    };
}

#endif //SIMSYSCOMPILER_CHARRVALUESTRUCTURE_H
