//
// Created by a_mod on 08.06.2019.
//

#pragma once
#include "BoolStructure.h"

namespace ACC {
    class BoolIValueStructure : public BoolStructure{
        bool value;

    public:
        bool getValue() const;

        explicit BoolIValueStructure(bool value);

        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;
        void loadToRegister(Register reg, Code& code) override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;
    };
}

