//
// Created by a_mod on 10.02.2019.
//

#include <Logger/Logger.h>
#include "IntermediateCode.h"
#include <IntermediateCodeGenerator/Optimizaions/Optimizations.h>

ACC::IntermediateCode::IntermediateCode(const AbstractSyntaxTree& tree) {
    code = Code();
    tree.getRoot()->asExpr()->generate(code);
}

void ACC::IntermediateCode::print() {
    LOG.createHeading("Generated Intermediate Representation");
    code.print();
}

void ACC::IntermediateCode::optimize() {
    LOG.createHeading("Running Copy Elision...");
    copyElision(code);
    code.print();

    LOG.createHeading("Running Constant Elision...");
    constantElision(code);
    code.print();
}
