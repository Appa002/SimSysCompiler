//
// Created by a_mod on 06.05.2019.
//

#ifndef SIMSYSCOMPILER_TYPEID_H
#define SIMSYSCOMPILER_TYPEID_H

#include <vector>

namespace ACC {
    struct TypeId {
        TypeId() = default;
        TypeId(size_t id, size_t size) : id(id), size(size){}

        size_t getId() const {return id;}
        size_t getSize() const {return size;}

        friend inline bool operator==(TypeId const &lhs, TypeId const &rhs) {
            return lhs.id == rhs.id && lhs.size == rhs.size;
        }

        friend inline bool operator!=(TypeId const &lhs, TypeId const &rhs) {
            return !(lhs == rhs);
        }

    private:
        size_t id = 0;
        size_t size = 0;
    };
}

#endif //SIMSYSCOMPILER_TYPEID_H
