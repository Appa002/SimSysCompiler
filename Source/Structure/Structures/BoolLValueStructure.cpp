//
// Created by a_mod on 07.06.2019.
//

#include "BoolLValueStructure.h"
#include <Assembly/Code.h>
#include <General/utils.h>
#include <General/builtinTypes.h>

ACC::BoolLValueStructure::BoolLValueStructure(std::string const & access) : GenericLValueStructure(Type(BuiltIns::numType), access) {

}