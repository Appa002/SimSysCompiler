//
// Created by a_mod on 31.08.2019.
//

#include "UserStructure.h"
#include <Error/Errors.h>
#include <Assembly/Code.h>

ACC::UserStructure::UserStructure(ACC::ValueCategory v, const ACC::Type& t) : ComplexStructure(v, t), type(t), valueCategory(v){

}