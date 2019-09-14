//
// Created by a_mod on 01.09.2019.
//

#pragma once

#include <Structure/AsmAccessible.h>
#include <string>
#include "UserStructure.h"

namespace ACC {
    class UserLValueStructure : public UserStructure, public AsmAccessible {
    protected:
        std::string access;
    public:
        explicit UserLValueStructure(std::string  access, const Type& type);

        std::shared_ptr<Structure> operatorCopy(std::vector<std::shared_ptr<Structure>> objList, Code &) override;
        std::shared_ptr<Structure> operatorDot(Code &code, std::string member) override;


        std::shared_ptr<Structure> operatorAdd(std::shared_ptr<Structure> amount, Code &code) override;




        bool haveSameTypes(std::vector<Type> a, std::vector<std::shared_ptr<Structure>> b);

        std::string const & getAccess() const override;

    };
}
