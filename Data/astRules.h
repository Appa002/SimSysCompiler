//
// Created by a_mod on 23.01.2019.
//

#ifndef SIMSYSCOMPILER_ASSOPERATORS_H
#define SIMSYSCOMPILER_ASSOPERATORS_H

#include <vector>
#include <grammar.h>
#include <functional>
#include <AbstractSyntaxTree/ASTNode.h>
#include <AbstractSyntaxTree/Rule.h>

namespace ACC::data{

    /*! Returns a vector with all Rules for turning a Parse Tree to a Abstract Syntax Tree.*/
    std::vector<Rule> getRules();
}

#endif //SIMSYSCOMPILER_ASSOPERATORS_H
