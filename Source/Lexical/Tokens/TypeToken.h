#include <utility>

#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#pragma once

#include <Lexical/IToken.h>
#include <General/Type.h>

namespace ACC{
    struct TypeToken : public IToken{

        TypeToken() : IToken(Symbol::TYPE, 0) {}
        TypeToken(std::string str, Type typeId) : type(std::move(str)), typeId(typeId), IToken(Symbol::TYPE, 0) {}

        std::string type;
        Type typeId = Type(0, 0);

        std::string getIdentifier() override{
            return "Type \'" + type + "\' Id: " + std::to_string(typeId.getId());
        }

        [[nodiscard]] std::string getIdForErrReporting() const override{
            return "type";
        };

        friend inline bool operator==(TypeToken const & lhs, TypeToken const & rhs){
            return lhs.type == rhs.type && lhs.typeId == rhs.typeId;
        }
    };
}

