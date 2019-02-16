//
// Created by a_mod on 11.02.2019.
//

#ifndef SIMSYSCOMPILER_OPTIMIZATIONS_H
#define SIMSYSCOMPILER_OPTIMIZATIONS_H

#include <IntermediateCodeGenerator/Code.h>

namespace ACC{
    void copyElision(Code& input);
    void constantElision(Code &input);
}

#endif //SIMSYSCOMPILER_OPTIMIZATIONS_H
