//
// Created by a_mod on 18.01.2019.
//

#include <stdexcept>
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
        }
        throw std::runtime_error("Symbol not known.");
}
