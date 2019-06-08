//
// Created by a_mod on 07.06.2019.
//

#ifndef SIMSYSCOMPILER_BOOLRVALUESTRUCTURE_H
#define SIMSYSCOMPILER_BOOLRVALUESTRUCTURE_H

#include "Structure/Structures/ElementaryStructure.h"

namespace ACC {
    class BoolRValueStructure : public ElementaryStructure{
    public:
        Register reg;

        explicit BoolRValueStructure(Register reg);
        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;
        std::shared_ptr<Structure> operatorEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorNotEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorLess(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorGreater(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorLessEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorGreaterEqual(std::shared_ptr<Structure> other, Code &code) override;

        void loadToRegister(Register reg, Code& code) override;

    };
}

#endif //SIMSYSCOMPILER_BOOLRVALUESTRUCTURE_H
