//
// Created by a_mod on 11.02.2019.
//

#include <IntermediateCodeGenerator/Optimizaions/Optimizations.h>
#include <Logger/Logger.h>
#include "Optimizations.h"

using namespace ACC;


void ACC::copyElision(Code& input){
    size_t i = 0;
    for(auto op : input){
        if(op->id == OperatorId::COPY)
            input.removeUnary(i);
        i++;
    }
}