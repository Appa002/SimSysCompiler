//
// Created by a_mod on 11.02.2019.
//

#include <IntermediateCodeGenerator/Optimizaions/Optimizations.h>
#include <Logger/Logger.h>
#include "Optimizations.h"

using namespace ACC;


void ACC::copyElision(Code &input) {
    bool hasChanged = false;
    do {
        hasChanged = false;
        for (size_t i = 0; i < input.getData().size(); i++) {
            if (input.at(i)->id == OperatorId::COPY) {
                input.removeUnary(i);
                hasChanged = true;
            }
        }
    } while (hasChanged);
}

