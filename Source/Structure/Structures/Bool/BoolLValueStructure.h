//
// Created by a_mod on 03.06.2019.
//
#pragma once
#include <Structure/Structure.h>
#include "Structure/Structures/ElementaryStructure.h"
#include "Structure/Structures/GenericLValueStructure.h"

#include "BoolStructure.h"

namespace ACC{
    class BoolLValueStructure : public BoolStructure, public AsmAccessible{
    protected:
        std::string access;
    public:
        std::string const & getAccess() const override;
        explicit BoolLValueStructure(std::string access);

        void loadToRegister(Register reg, Code& code) override;
        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;

        bool hasConversionTo(const Type &id) override;

    };
}
