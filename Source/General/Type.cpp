#include "Type.h"

ACC::Type::Type(size_t id, size_t size)  : id(TypeId(id, size)) {

}

size_t ACC::Type::getId() const
    { return id.getId(); }

size_t ACC::Type::getSize() const { return id.getSize(); }

ACC::TypeId ACC::Type::getPointingTo() const {
    return pointingTo;
}

ACC::Type::Type(size_t id, size_t size, ACC::TypeId other) : id(TypeId(id, size)), pointingTo(other){
}

ACC::Type::Type(ACC::TypeId id) : id(id) {

}

ACC::Type::Type(const ACC::TypeId & first, ACC::TypeId other) : id(first), pointingTo(other) {

}
