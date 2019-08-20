//
// Created by a_mod on 20.08.2019.
//

#include "TypeTable.h"

ACC::TypeTable::TypeTable() {
    // Builtin Types;

    addType("char", 1, {});
    addType("bool", 1, {});
    addType("num", 8, {});

}

bool ACC::TypeTable::isType(std::string const &id) {
    return sizeMap.find(id) != sizeMap.cend();
}

size_t ACC::TypeTable::getSize(std::string const &id) {
    if(!isType(id))
        throw std::runtime_error("Not a type.");
    return sizeMap.at(id);
}

void ACC::TypeTable::addType(std::string const &id, size_t size, const std::vector<std::string>& conversions) {
    sizeMap[id] = size;
}

