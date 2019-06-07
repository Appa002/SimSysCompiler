//
// Created by a_mod on 07.06.2019.
//

#ifndef SIMSYSCOMPILER_NUMOPERATOR_H
#define SIMSYSCOMPILER_NUMOPERATOR_H

#include <Structure/Structure.h>

namespace ACC {
    class ElementaryStructure : public Structure{
    public:
        virtual void loadToRegister(Register reg, Code& code) = 0;
    };
}

#endif //SIMSYSCOMPILER_NUMOPERATOR_H
