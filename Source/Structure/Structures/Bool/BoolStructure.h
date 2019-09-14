//
// Created by a_mod on 08.06.2019.
//

#ifndef SIMSYSCOMPILER_BOOLSTRUCTURE_H
#define SIMSYSCOMPILER_BOOLSTRUCTURE_H

#include <Structure/Structures/ElementaryStructure.h>

namespace ACC {
    class BoolStructure : public ElementaryStructure{
    public:
        explicit BoolStructure(ValueCategory v);

        std::shared_ptr<Structure> operatorEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorNotEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorLess(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorGreater(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorLessEqual(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorGreaterEqual(std::shared_ptr<Structure> other, Code &code) override;

        std::shared_ptr<Structure> operatorOr(std::shared_ptr<Structure> other, Code &code) override;
        std::shared_ptr<Structure> operatorAnd(std::shared_ptr<Structure> other, Code &code) override;
    };
}

#endif //SIMSYSCOMPILER_BOOLSTRUCTURE_H
