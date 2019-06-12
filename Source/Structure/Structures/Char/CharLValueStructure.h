//
// Created by a_mod on 08.06.2019.
//

#ifndef SIMSYSCOMPILER_CHARLVALUESTRUCTURE_H
#define SIMSYSCOMPILER_CHARLVALUESTRUCTURE_H

#include "CharStructure.h"
#include <Structure/AsmAccessible.h>

namespace ACC {
    class CharLValueStructure : public CharStructure, public AsmAccessible{
    protected:
        std::string access;
    public:
        explicit CharLValueStructure(std::string const & access);

        void loadToRegister(Register reg, Code& code) override;
        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;
        std::string const & getAccess() const override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;
    };
}

#endif //SIMSYSCOMPILER_CHARLVALUESTRUCTURE_H
