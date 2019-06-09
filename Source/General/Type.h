//
// Created by a_mod on 06.05.2019.
//
#pragma once

#include <vector>

namespace ACC {

    struct TypeId{
        TypeId() = default;
        TypeId(size_t id, size_t size) : id(id), size(size) {}

        size_t getId() const { return id; };
        size_t getSize() const { return size; };

        friend bool operator==(TypeId const & lhs, TypeId const & rhs){
            return lhs.id == rhs.id && lhs.size == rhs.size;
        };

        friend bool operator!=(TypeId const & lhs, TypeId const & rhs){
            return !(lhs == rhs);
        };
    private:
        size_t id = 0;
        size_t size = 0;
    };

    class Type {
    public:
        Type() = default;
        Type(size_t id, size_t size);
        Type(size_t id, size_t size, TypeId other);

        explicit Type(TypeId);
        Type(TypeId const &, TypeId other);

        size_t getId() const;
        size_t getSize() const;
        TypeId getTypeId() const;
        TypeId getPointingTo() const;

        Type& operator=(TypeId const & other){
            pointingTo = TypeId(0, 0);
            id = other;
            return *this;
        }

        friend bool operator==(Type const & lhs, Type const & rhs){
            return lhs.id.getId() == rhs.id.getId() && lhs.id.getSize() == rhs.id.getSize();
        };

        friend bool operator!=(Type const & lhs, Type const & rhs){
            return !(lhs == rhs);
        };

        friend bool operator==(Type const & lhs, TypeId const & rhs){
            return lhs.id.getId() == rhs.getId() && lhs.id.getSize() == rhs.getSize();
        };

        friend bool operator!=(Type const & lhs, TypeId const & rhs){
            return !(lhs == rhs);
        };


    private:
        TypeId id = TypeId(0, 0);
        TypeId pointingTo = TypeId(0,0);
    };
}

