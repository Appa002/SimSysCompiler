//
// Created by a_mod on 03.06.2019.
//

#ifndef SIMSYSCOMPILER_NUMBUILTINTYPE_H
#define SIMSYSCOMPILER_NUMBUILTINTYPE_H

#include <Structure/Structure.h>
#include "Structure/Structures/ElementaryStructure.h"
#include "NumStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"

namespace ACC{
    class NumLValueStructure : public NumStructure, public AsmAccessible{
    protected:
        std::string access;
    public:
        explicit NumLValueStructure(std::string const & access);

        void loadToRegister(Register reg, Code& code) override;
        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;
        std::string const & getAccess() const override;

    };
}

#endif //SIMSYSCOMPILER_NUMBUILTINTYPE_H
