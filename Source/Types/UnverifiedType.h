//
// Created by a_mod on 06.05.2019.
//
#pragma once

#include <string>
#include <utility>

namespace ACC {

    class UnverifiedType {
    private:
        UnverifiedType(std::string id, bool isPtr) : id(std::move(id)), isPtr(isPtr) {};


    public:
        UnverifiedType() = default;
        explicit UnverifiedType(std::string id) : id(std::move(id)) {};


        std::string id;
        bool isPtr = false;

        friend bool operator==(UnverifiedType const & lhs, UnverifiedType const & rhs){
            return lhs.id == rhs.id && lhs.isPtr == rhs.isPtr;
        };

        friend bool operator!=(UnverifiedType const & lhs, UnverifiedType const & rhs){
            return !(lhs == rhs);
        };

        static UnverifiedType createPtr(std::string id){
            return UnverifiedType(std::move(id), true);
        }

    };
}

