//
// Created by a_mod on 07.06.2019.
//
#pragma once
#include <Structure/Structures/ElementaryLValueStructure.h>

namespace ACC {
    class PtrLValueStructure : public ElementaryLValueStructure {
    public:
        explicit PtrLValueStructure(std::string access);

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


    };
}

