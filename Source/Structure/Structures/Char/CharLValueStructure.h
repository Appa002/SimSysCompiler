//
// Created by a_mod on 08.06.2019.
//

#ifndef SIMSYSCOMPILER_CHARLVALUESTRUCTURE_H
#define SIMSYSCOMPILER_CHARLVALUESTRUCTURE_H

#include "CharStructure.h"

namespace ACC {
    class CharLValueStructure : public CharStructure{
    protected:
        std::string access;
    public:
        explicit CharLValueStructure(std::string const & access);

        void loadToRegister(Register reg, Code& code) override;
        std::shared_ptr<Structure> operatorCopy(std::shared_ptr<Structure> address, Code &) override;
        std::string getAccess() const;
    };
}

#endif //SIMSYSCOMPILER_CHARLVALUESTRUCTURE_H
