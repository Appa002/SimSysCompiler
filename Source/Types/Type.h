//
// Created by a_mod on 06.05.2019.
//
#pragma once

#include <string>
#include <utility>
#include "TypeField.h"
#include <vector>
#include <unordered_map>

namespace ACC {

    class Type {
    private:
        Type(std::string id, size_t size, bool isPtr) : id(std::move(id)), size(size), isPtr(isPtr) {};
        Type(std::string id, size_t size, bool isPtr, std::unordered_map<std::string, TypeField> fields)
        : id(std::move(id)), size(size), isPtr(isPtr), fields(std::move(fields)) {};


    public:
        Type() = default;
        Type(std::string id, size_t size) : id(std::move(id)), size(size) {};
        Type(std::string id, size_t size, std::unordered_map<std::string, TypeField> fields) : id(std::move(id)), size(size), fields(std::move(fields)) {}


        std::string id;
        size_t size = 0;
        bool isPtr = false;
        std::unordered_map<std::string, TypeField> fields;
        std::unordered_map<std::string, size_t> fieldSizes;

        bool isComplex = false;


        friend bool operator==(Type const & lhs, Type const & rhs){
            return lhs.id == rhs.id && lhs.size == rhs.size && lhs.isPtr == rhs.isPtr;
        };

        friend bool operator!=(Type const & lhs, Type const & rhs){
            return !(lhs == rhs);
        };

        static Type createPtr(const Type& other){
            return Type(other.id, 8, true, other.fields);
        }

        static Type createPtr(std::string id){
            return Type(std::move(id), 8, true);
        }

        static Type createPtr(std::string id, std::unordered_map<std::string, TypeField> fields){
            return Type(std::move(id), 8, true, std::move(fields));
        }


    };
}

