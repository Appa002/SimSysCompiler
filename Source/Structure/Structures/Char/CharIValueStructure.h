//
// Created by a_mod on 08.06.2019.
//

#ifndef SIMSYSCOMPILER_CHARIVALUESTRUCTURE_H
#define SIMSYSCOMPILER_CHARIVALUESTRUCTURE_H

#include "CharStructure.h"

namespace ACC {
    class CharIValueStructure : public CharStructure{
        uint8_t value;

    public:
        uint8_t getValue() const;

        explicit CharIValueStructure(uint8_t value);

        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;
        void loadToRegister(Register reg, Code& code) override;
    };
}

#endif //SIMSYSCOMPILER_CHARIVALUESTRUCTURE_H
