//
// Created by a_mod on 20.08.2019.
//

#include "TypeTable.h"

#include <utility>

ACC::TypeTable::TypeTable() {
    // Builtin Types;

    addType("char", Type("char", 1));
    addType("bool", Type("bool", 1));
    addType("num", Type("num", 8));

}

bool ACC::TypeTable::isType(std::string const &id) {
    return typeMap.find(id) != typeMap.cend();
}

size_t ACC::TypeTable::getSize(std::string const &id) {
    if(!isType(id))
        throw std::runtime_error("Not a type.");
    return typeMap.at(id).size;
}

ACC::Type ACC::TypeTable::getType(std::string const &id){
    if(!isType(id))
        throw std::runtime_error("Not a type.");
    return typeMap.at(id);
}

void ACC::TypeTable::addType(std::string const &id, Type info) {
    typeMap[id] = std::move(info);
}

