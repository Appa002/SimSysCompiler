#include <utility>

#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_LITERALTOKEN_H
#define SIMSYSCOMPILER_LITERALTOKEN_H

#include <Lexical/IToken.h>
#include <GeneralDataStore.h>
#include <utils.h>

namespace ACC{
    enum class LiteralKind{
        NUMBER,
        STRING
    };

    struct LiteralToken : public IToken{
        LiteralToken(std::string l, LiteralKind k) : IToken(), kind(k) {
            id = Symbol::LITERAL;
            literal.storeT(std::move(l));
        };

        LiteralToken(uint64_t l, LiteralKind k) : IToken(), kind(k) {
            id = Symbol::LITERAL;
            if(l <= 0xFF)
                literal.storeT((uint8_t)l);
            else if(l <= 0xFFff)
                literal.storeT((uint16_t)l);
            else if(l <= 0xFFffFF)
                literal.storeT((uint32_t)l);
            else if(l <= 0xFFffFFff)
                literal.storeT((uint64_t)l);
        };

        GeneralDataStore literal;
        LiteralKind kind;


        std::string getIdentifier() override {
            std::string data = (kind == LiteralKind::NUMBER) ?
                    "0x" + toHex(literal.asT<uint64_t>()) : literal.asT<std::string>();

            std::string kindStr = (kind == LiteralKind::NUMBER) ? ("number") : ("string");

            return "Literal "+ kindStr +" (" + data + ")";
        }

        friend inline bool operator==(LiteralToken const & lhs, LiteralToken const & rhs){
            bool out = lhs.kind == rhs.kind;
            return out && lhs.literal == rhs.literal;
        }
    };
}

#endif //SIMSYSCOMPILER_LITERALTOKEN_H
