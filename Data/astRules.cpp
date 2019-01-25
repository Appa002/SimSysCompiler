
#include <astRules.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <AbstractSyntaxTree/process.h>
#include <AbstractSyntaxTree/ASTNode.h>
#include <Lexical/Tokens/MathOperatorToken.h>
#include <Parser/Production.h>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/PrintToken.h>

/*
 *
            {Symbol::start,       {Symbol::assignment}},
            {Symbol::start,       {Symbol::key}},

            {Symbol::assignment,  {Symbol::VAR, Symbol::ID, Symbol::expr,  Symbol::EOS}},
            {Symbol::key,         {Symbol::PRINT,  Symbol::EOS}},

            {Symbol::expr,        {Symbol::LITERAL}}, // E ::= A-Za-z0-9
            {Symbol::expr,        {Symbol::BRACKET, Symbol::expr,          Symbol::BRACKET}}, // (E)
            {Symbol::expr,        {Symbol::expr,    Symbol::MATH_OPERATOR, Symbol::expr}} // E-E
 * */

std::vector<ACC::Rule> ACC::data::getRules() {
    return { // vector
        {{Symbol::start, {Symbol::assignment}}, [](auto children){
            return process(children[0]);
        }},

        {{Symbol::start, {Symbol::key}}, [](auto children){
            return process(children[0]);
        }},

        {{Symbol::assignment, {Symbol::VAR, Symbol::ID, Symbol::expr,  Symbol::EOS}}, [](auto children){
            std::string sym = static_cast<IdToken*>(children[1]->token)->sym;
            auto vec = {new ASTNode(AstOperator::ID, sym), process(children[2])};
            return new ASTNode(AstOperator::ASSIGN, vec);
        }},


        {{Symbol::key, {Symbol::PRINT,  Symbol::EOS}}, [](auto children) {
            auto asPrintToken = static_cast<PrintToken*>(children[0]->token);
            return new ASTNode(AstOperator::PRINT, {new ASTNode(AstOperator::ID, asPrintToken->sym)});
        }},


        {{Symbol::expr, {Symbol::LITERAL}}, [](std::vector < ACC::ParseNode * > children) {
            return new ASTNode(AstOperator::LITERAL, static_cast<LiteralToken*>(children[0]->token)->literal);
        }},

        {{Symbol::expr, {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET}}, [](std::vector < ACC::ParseNode * > children){
            return process(children[1]);
        }},

        {{Symbol::expr, {Symbol::expr, Symbol::MATH_OPERATOR, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children){
            auto vec = {process(children[0]), process(children[2])};
            switch (static_cast<MathOperatorToken*>(children[1]->token)->kind){
                case MathOperators::PLUS:
                    return new ASTNode(AstOperator::PLUS, vec);
                case MathOperators::MINUS:
                    return new ASTNode(AstOperator::MINUS, vec);
        }
        }}

    };
}