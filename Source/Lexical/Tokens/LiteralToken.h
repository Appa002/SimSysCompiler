#include <utility>

#include <utility>

//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_LITERALTOKEN_H
#define SIMSYSCOMPILER_LITERALTOKEN_H

#include <Lexical/IToken.h>
#include <General/GeneralDataStore.h>
#include <General/utils.h>
#include <General/Type.h>
#include <General/builtinTypes.h>

namespace ACC{

    struct LiteralToken : public IToken{
        LiteralToken(std::string l, Type k) : IToken(Symbol::LITERAL, 0), type(k) {
            id = Symbol::LITERAL;
            literal.storeT(std::move(l));
        };

        LiteralToken(char c, Type k) : IToken(Symbol::LITERAL, 0), type(k) {
            id = Symbol::LITERAL;
            literal.storeT(c);
        };


        LiteralToken(uint64_t l, Type k) : IToken(Symbol::LITERAL, 0), type(k) {
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
        Type type;


        std::string getIdentifier() override {
            if(type == BuiltIns::charType || type == BuiltIns::numType){
                return "Literal (Arithmetic): 0x" + toHex(literal.createNumber());
            }
            else if(type == BuiltIns::ptrType){
                auto out = literal.asT<std::string>();
                size_t i = 0;
                for(char& c : out){
                    if(c=='\n'){
                        out.erase(i, 2);
                        out.insert(i, "\\n");
                    }
                    i++;
                }

                return "Literal (String): \"" + out +"\"";
            }
            else{
                std::string data = "[ ";
                for(size_t i = 0; i < literal.size(); i++){
                    data += " `" + toHex(literal.at(i)) + "`";
                    if(i + 1 < literal.size())
                        data += ",";
                }
                data += " ]";

                return "Literal (Array): " + data;
            }
        }

        friend inline bool operator==(LiteralToken const & lhs, LiteralToken const & rhs){
            bool out = lhs.type == rhs.type;
            return out && lhs.literal == rhs.literal;
        }
    };
}
#endif //SIMSYSCOMPILER_LITERALTOKEN_H
