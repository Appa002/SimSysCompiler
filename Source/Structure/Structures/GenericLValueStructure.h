//
// Created by a_mod on 07.06.2019.
//

#ifndef SIMSYSCOMPILER_ELEMENTARYLVALUESTRUCTURE_H
#define SIMSYSCOMPILER_ELEMENTARYLVALUESTRUCTURE_H

#include "ElementaryStructure.h"
#include <Structure/AsmAccessible.h>

namespace ACC {
    class GenericLValueStructure : public AsmAccessible, public ElementaryStructure{
    private:
        std::string access;
    public:
        std::string const & getAccess() const override;
        explicit GenericLValueStructure(Type type, std::string access);

        void loadToRegister(Register reg, Code& code) override;
        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> obj, Code &) override;

        std::shared_ptr<Structure> operatorChar(Code & code) override;
        std::shared_ptr<Structure> operatorNum(Code & code) override;
        std::shared_ptr<Structure> operatorBool(Code & code) override;
        std::shared_ptr<Structure> operatorPtr(Code &code, Type pointingTo) override;

    };
}

#endif //SIMSYSCOMPILER_ELEMENTARYLVALUESTRUCTURE_H
