//
// Created by a_mod on 07.06.2019.
//
#pragma once
#include <Structure/Structures/GenericLValueStructure.h>
#include "PtrStructure.h"
#include <Structure/AsmAccessible.h>

namespace ACC {
    class PtrLValueStructure : public PtrStructure, public AsmAccessible {
    protected:
        std::string access;
    public:
        std::string const & getAccess() const override;
        PtrLValueStructure(std::string access, Type type);

        void loadToRegister(Register reg, Code& code) override;
        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> obj, Code &) override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;

        bool hasConversionTo(const Type &id) override;

    };
}

