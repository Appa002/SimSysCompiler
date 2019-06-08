//
// Created by a_mod on 07.06.2019.
//

#ifndef SIMSYSCOMPILER_NUMOPERATORRVALUE_H
#define SIMSYSCOMPILER_NUMOPERATORRVALUE_H

#include <Structure/Structure.h>
#include "Structure/Structures/ElementaryStructure.h"
#include <Structure/Structures/Number/NumStructure.h>

namespace ACC {
    class NumRValueStructure : public NumStructure {
    private:
        Register reg;
    public:
        explicit NumRValueStructure(Register reg);

        void loadToRegister(Register reg, Code& code) override;

        std::shared_ptr<ACC::Structure> operatorCopy(std::shared_ptr<Structure> address, ACC::Code &code) override;

    };
}

#endif //SIMSYSCOMPILER_NUMOPERATORRVALUE_H
