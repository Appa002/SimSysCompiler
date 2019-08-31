//
// Created by a_mod on 08.06.2019.
//

#pragma once

#include <Structure/ImmediatAccessible.h>
#include "PtrStructure.h"

namespace ACC {
    class PtrIValueStructure : public PtrStructure, public ImmediatAccessible{
        uint64_t value;

    public:
        std::string getValue() const override;

        explicit PtrIValueStructure(uint64_t value, Type pointingTo);

        void loadToRegister(Register reg, Code& code) override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;

        bool hasConversionTo(const Type &id) override;

    };
}

