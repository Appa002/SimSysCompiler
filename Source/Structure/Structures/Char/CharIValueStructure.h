//
// Created by a_mod on 08.06.2019.
//

#ifndef SIMSYSCOMPILER_CHARIVALUESTRUCTURE_H
#define SIMSYSCOMPILER_CHARIVALUESTRUCTURE_H

#include <Structure/ImmediatAccessible.h>
#include "CharStructure.h"

namespace ACC {
    class CharIValueStructure : public CharStructure, public ImmediatAccessible{
        uint8_t value;

    public:
        std::string getValue() const;

        explicit CharIValueStructure(uint8_t value);

        void loadToRegister(Register reg, Code& code) override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;

        bool hasConversionTo(const Type &id) override;

    };
}

#endif //SIMSYSCOMPILER_CHARIVALUESTRUCTURE_H
