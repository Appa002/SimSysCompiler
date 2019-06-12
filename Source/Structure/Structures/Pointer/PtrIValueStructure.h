//
// Created by a_mod on 08.06.2019.
//

#pragma once
#include "PtrStructure.h"

namespace ACC {
    class PtrIValueStructure : public PtrStructure{
        uint64_t value;

    public:
        uint64_t getValue() const;

        explicit PtrIValueStructure(uint64_t value, Type pointingTo);

        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;
        void loadToRegister(Register reg, Code& code) override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;
    };
}

