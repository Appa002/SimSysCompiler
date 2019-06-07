//
// Created by a_mod on 10.02.2019.
//

#include <Logger/Logger.h>
#include "Assembly.h"

ACC::Assembly::Assembly(const AbstractSyntaxTree& tree) {
    code = Code();
    tree.getRoot()->generate(code);
}

void ACC::Assembly::print() {
    LOG.createHeading("Generated Intermediate Representation");
    LOG() << code.combineOutput();
}

void ACC::Assembly::optimize() {
   /* LOG.createHeading("Running Copy Elision...");
    copyElision(code);
    code.print();

    LOG.createHeading("Running Constant Elision...");
    constantElision(code);
    LOG() << "" << std::endl;
    LOG() << Log::Colour::Blue << "New Intermediate Representation:" << std::endl;
    code.print();*/
}

const ACC::Code &ACC::Assembly::getCode() const{
    return code;
}

void ACC::Assembly::writeToFile(std::string path) {
    std::fstream file(path, std::ios::trunc | std::ios::out);
    if (!file.is_open())
        throw std::runtime_error("Couldn't open output file at path: \"" + path + "\"");

    file << code.combineOutput();
    file.close();
}
