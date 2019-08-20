//
// Created by a_mod on 06.05.2019.
//
#pragma once

#include <string>
#include <utility>

namespace ACC {

    class Type {
    private:
        Type(std::string id, size_t size, bool isPtr) : id(std::move(id)), size(size), isPtr(isPtr) {};


    public:
        Type() = default;
        Type(std::string id, size_t size) : id(std::move(id)), size(size) {};


        std::string id;
        size_t size = 0;
        bool isPtr = false;



        friend bool operator==(Type const & lhs, Type const & rhs){
            return lhs.id == rhs.id && lhs.size == rhs.size && lhs.isPtr == rhs.isPtr;
        };

        friend bool operator!=(Type const & lhs, Type const & rhs){
            return !(lhs == rhs);
        };

        static Type createPtr(std::string id){
            return Type(std::move(id), 8, true);
        }

    };
}

