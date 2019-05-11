#include <utility>

#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>
#include <TypeId.h>

namespace ACC{
    struct TypeToken : public IToken{
        TypeToken() : IToken() {this->id = Symbol::TYPE;}
        TypeToken(std::string str, TypeId typeId) : type(std::move(str)), typeId(typeId) {this->id = Symbol::TYPE;}

        std::string type;
        TypeId typeId = TypeId(0, 0);

        std::string getIdentifier() override{
            return "Type \'" + type + "\' Id: " + std::to_string(typeId.getId());
        }

        friend inline bool operator==(TypeToken const & lhs, TypeToken const & rhs){
            return lhs.type == rhs.type && lhs.typeId == rhs.typeId;
        }
    };
}

