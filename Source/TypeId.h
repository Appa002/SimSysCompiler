//
// Created by a_mod on 06.05.2019.
//

#ifndef SIMSYSCOMPILER_TYPEID_H
#define SIMSYSCOMPILER_TYPEID_H

namespace ACC {
    struct TypeId {
        TypeId() = default;
        TypeId(size_t id) : id(id) {}

        size_t toInt() {return id;}

        friend inline bool operator==(TypeId const &lhs, TypeId const &rhs) {
            return lhs.id == rhs.id;
        }

        friend inline bool operator!=(TypeId const &lhs, TypeId const &rhs) {
            return lhs.id != rhs.id;
        }

    private:
        size_t id = 0;
    };
}

#endif //SIMSYSCOMPILER_TYPEID_H
