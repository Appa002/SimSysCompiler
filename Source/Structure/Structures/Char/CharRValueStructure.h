//
// Created by a_mod on 08.06.2019.
//

#ifndef SIMSYSCOMPILER_CHARRVALUESTRUCTURE_H
#define SIMSYSCOMPILER_CHARRVALUESTRUCTURE_H

#include "CharStructure.h"

namespace ACC {
    class CharRValueStructure : public CharStructure{
    private:
        Register reg;
    public:
        explicit CharRValueStructure(Register reg);

        void loadToRegister(Register reg, Code& code) override;

        std::shared_ptr<ACC::Structure> operatorCopy(std::shared_ptr<Structure> address, ACC::Code &code) override;

    };
}

#endif //SIMSYSCOMPILER_CHARRVALUESTRUCTURE_H
