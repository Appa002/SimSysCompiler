
#include <astRules.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <AbstractSyntaxTree/process.h>
#include <AbstractSyntaxTree/ASTNode.h>
#include <Lexical/Tokens/MathOperatorToken.h>
#include <Parser/Production.h>

std::vector<ACC::Rule> ACC::data::getRules() {
    return { // vector
    /* start ::= stmt */    {{Symbol::start, {Symbol::stmt}}, [](auto children){
        return process(children[0]);
        }},

    /* stmt ::= expr EOS stmt */    {{Symbol::stmt, {Symbol::expr, Symbol::EOS, Symbol::stmt}}, [](auto children){
        auto vec = {process(children[0]), process(children[2])};
        return new ASTNode(AstOperator::STMT, vec);
    }},

            /* stmt ::= expr EOS*/    {{Symbol::stmt, {Symbol::expr, Symbol::EOS}}, [](auto children){
        return new ASTNode(AstOperator::STMT, {process(children[0])});
    }},

    /* E ::= Literal */    {{Symbol::expr, {Symbol::LITERAL}}, [](std::vector < ACC::ParseNode * > children) {
        return new ASTNode(AstOperator::LITERAL, static_cast<LiteralToken*>(children[0]->token)->literal);
        }},

        /* E ::= (E) */     {{Symbol::expr, {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET}}, [](std::vector < ACC::ParseNode * > children){
        return process(children[1]);
        }},

        /* E ::= E+E */     {{Symbol::expr, {Symbol::expr, Symbol::MATH_OPERATOR, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children){
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