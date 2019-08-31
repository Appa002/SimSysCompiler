//
// Created by a_mod on 31.08.2019.
//

#pragma once

#include <Structure/Structure.h>
#include <Structure/Structures/ComplexStructure.h>

namespace ACC {
    class UserStructure : public ComplexStructure {
    public:
        ValueCategory valueCategory;
        Type type;

        UserStructure(ValueCategory v, const Type& t);

        void loadAddress(Register reg, Code& code) override {};

        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> obj, Code &) override;

        bool hasCopyFunc = true;

/*
        std::shared_ptr<Structure> operatorForDone(std::shared_ptr<Structure> limit, Code &code) override;
        std::shared_ptr<Structure> operatorForNext(Code &) override;
        std::shared_ptr<Structure> operatorAdd(std::shared_ptr<Structure> amount, Code &code) override;
        std::shared_ptr<Structure> operatorSubtract(std::shared_ptr<Structure> amount, Code &) override;
        std::shared_ptr<Structure> operatorMultiplication(std::shared_ptr<Structure> amount, Code &code) override;
        std::shared_ptr<Structure> operatorDivision(std::shared_ptr<Structure> amount, Code &code) override;
        std::shared_ptr<Structure> operatorEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorNotEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorLess(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorGreater(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorLessEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorGreaterEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorDereference(Code &code) override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;

        bool hasConversionTo(const Type &id) override;
        */


    };
}

