//
// Created by a_mod on 07.06.2019.
//

#ifndef SIMSYSCOMPILER_NUMIVALUESTRUCTURE_H
#define SIMSYSCOMPILER_NUMIVALUESTRUCTURE_H

#include <Structure/Structure.h>
#include <Structure/Structures/ElementaryStructure.h>
#include <Structure/Structures/Number/NumStructure.h>

namespace ACC {
    class NumIValueStructure : public NumStructure{
        int64_t value;

    public:
        int64_t getValue() const;

        explicit NumIValueStructure(int64_t value);

        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;
        void loadToRegister(Register reg, Code& code) override;
    };
}

#endif //SIMSYSCOMPILER_NUMIVALUESTRUCTURE_H
