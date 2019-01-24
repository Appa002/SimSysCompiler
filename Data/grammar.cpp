//
// Created by a_mod on 18.01.2019.
//

#include <stdexcept>
#include "grammar.h"

bool ACC::isNoneterminal(Symbol sys) {
        return sys > Symbol::none_terminals_start;

}

std::vector<ACC::production> ACC::data::getGrammar() {
        return {
                {Symbol::start, {Symbol::stmt}}, // start := stmt
                {Symbol::stmt, {Symbol::expr, Symbol::EOS, Symbol::stmt}}, // S ::= E EOS
                {Symbol::stmt, {Symbol::expr, Symbol::EOS}}, // S ::= E EOS

                {Symbol::expr, {Symbol::LITERAL}}, // E ::= A-Za-z0-9
                {Symbol::expr, {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET}}, // (E)
                {Symbol::expr, {Symbol::expr, Symbol::MATH_OPERATOR, Symbol::expr}} // E-E
        };
}

std::string ACC::data::symbolToString(ACC::Symbol s) {
        switch(s){
                case Symbol::VAR:
                        return "var";
                case Symbol::ID:
                        return "id";
                case Symbol::BRACKET:
                        return "bracket";
                case Symbol::MATH_OPERATOR:
                        return "math operator";
                case Symbol::PRINT:
                        return "print";
                case Symbol::LITERAL:
                        return "literal";
                case Symbol::EOS:
                        return "end of statement";
                case Symbol::none_terminals_start:
                        return "n_t_s";
                case Symbol::expr:
                        return "expr";
                case Symbol::stmt:
                        return "stmt";
                case Symbol::start:
                        return "start";
        }
        throw std::runtime_error("Symbol not known.");
}

std::string ACC::data::productionToString(ACC::production p) {
    std::string out = symbolToString(p.first);
    out += " ::= ";
    for(auto const& s : p.second){
        out+= "`" + symbolToString(s) + "` ";
    }
    return out;
}
