//
// Created by a_mod on 03.06.2019.
//

#ifndef SIMSYSCOMPILER_TYPE_H
#define SIMSYSCOMPILER_TYPE_H

#include <string>
#include <memory>
#include <General/Type.h>

namespace ACC {
    class Code;

    enum class Register{
        rA,
        rB,
        rC,
        rD,
        rSI,
        rDI,
        r8,
        r9,
        r10,
        r11,
        r12,
        r13,
        r14,
        r15,
    };

    enum class ValueCategory{
        rvalue,
        lvalue,
        ivalue
    };

class Structure : public std::enable_shared_from_this <Structure> {
    public:
        const ValueCategory vCategory;
        const Type type;

        std::vector<Register> registerInUse;

        Structure(ValueCategory valueCategory, Type type);
        virtual ~Structure();

        virtual std::shared_ptr<Structure> operatorForDone(std::shared_ptr<Structure> limit, Code &code);
        virtual std::shared_ptr<Structure> operatorForNext(Code &code);
        virtual std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &code);

        virtual std::shared_ptr<Structure> operatorAdd(std::shared_ptr<Structure> amount, Code &code);
        virtual std::shared_ptr<Structure> operatorSubtract(std::shared_ptr<Structure> amount, Code &code);
        virtual std::shared_ptr<Structure> operatorMultiplication(std::shared_ptr<Structure> amount, Code &code);
        virtual std::shared_ptr<Structure> operatorDivision(std::shared_ptr<Structure> amount, Code &code);

        virtual std::shared_ptr<Structure> operatorEqual(std::shared_ptr<Structure> other, Code &code);
        virtual std::shared_ptr<Structure> operatorNotEqual(std::shared_ptr<Structure> other, Code &code);

        virtual std::shared_ptr<Structure> operatorLess(std::shared_ptr<Structure> other, Code &code);
        virtual std::shared_ptr<Structure> operatorGreater(std::shared_ptr<Structure> other, Code &code);

        virtual std::shared_ptr<Structure> operatorLessEqual(std::shared_ptr<Structure> other, Code &code);
        virtual std::shared_ptr<Structure> operatorGreaterEqual(std::shared_ptr<Structure> other, Code &code);

        virtual std::shared_ptr<Structure> operatorNot(Code &code);
        virtual std::shared_ptr<Structure> operatorDereference(Code &code);

        void cleanUp(Code& code);

    };
}

#endif //SIMSYSCOMPILER_TYPE_H
