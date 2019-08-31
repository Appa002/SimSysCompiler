//
// Created by a_mod on 08.06.2019.
//

#pragma once
#include "BoolStructure.h"
#include <Structure/ImmediatAccessible.h>

namespace ACC {
    class BoolIValueStructure : public BoolStructure, ImmediatAccessible{
        bool value;

    public:
        std::string getValue() const override;

        explicit BoolIValueStructure(bool value);

        void loadToRegister(Register reg, Code& code) override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;

        bool hasConversionTo(const Type &id) override;
    };
}

