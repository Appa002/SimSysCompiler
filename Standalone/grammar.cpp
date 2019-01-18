//
// Created by a_mod on 18.01.2019.
//

#include "grammar.h"

bool ACC::isNoneterminal(Symbol sys) {
        return sys > Symbol::none_terminals_start;

}

std::vector<ACC::definition> ACC::data::getGrammar() {
        return {
                {Symbol::stmt, {Symbol::expr}}, // S ::= E
                {Symbol::expr, {Symbol::LITERAL}}, // E ::= A-Za-z0-9
                {Symbol::expr, {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET}}, // (E)
                {Symbol::expr, {Symbol::expr, Symbol::MATH_OPERATOR, Symbol::expr}} // E-E
        };
}
