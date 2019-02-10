//
// Created by a_mod on 10.02.2019.
//

#include <Logger/Logger.h>
#include "Code.h"

ACC::temporary ACC::Code::getSymbol(std::string sym) {
    return symTable.find(sym) == symTable.end() ? (0) : (symTable.at(sym));
}

ACC::temporary ACC::Code::emplaceSymbol(std::string sym) {
    symTable[sym] = ++temporaryCounter;
    return temporaryCounter;
}

void ACC::Code::emplaceOperator(const ACC::Operator &op) {
    data.emplace_back(op);
}

ACC::temporary ACC::Code::getLastTemporary() {
    return temporaryCounter;
}

ACC::temporary ACC::Code::createTemporary() {
    return ++temporaryCounter;
}

std::vector<ACC::Operator, std::allocator<ACC::Operator>>::iterator ACC::Code::begin() {
    return data.begin();
}

std::vector<ACC::Operator, std::allocator<ACC::Operator>>::iterator ACC::Code::end() {
    return data.end();
}
