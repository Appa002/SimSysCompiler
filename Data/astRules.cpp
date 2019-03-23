
#include <astRules.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <AbstractSyntaxTree/process.h>
#include <AbstractSyntaxTree/ASTNode.h>
#include <Lexical/Tokens/MathOperatorToken.h>
#include <Parser/Production.h>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/PrintToken.h>
#include <Lexical/Tokens/DeclToken.h>

/*
 *
 *
            {Symbol::call,        {Symbol::ID, Symbol::BRACKET, Symbol::BRACKET}},
            {Symbol::call,        {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET}},


            {Symbol::paramsList,  {Symbol::ID}},
            {Symbol::paramsList,  {Symbol::ID, Symbol::COMMA, Symbol::paramsList}},

            {Symbol::paramsList,  {Symbol::LITERAL}},
            {Symbol::paramsList,  {Symbol::LITERAL, Symbol::COMMA, Symbol::paramsList}},

              {Symbol::start,       {Symbol::assignment, Symbol::EOS}},
            {Symbol::start,       {Symbol::function, Symbol::EXTENT}},
            {Symbol::start,       {Symbol::keyword, Symbol::EOS}},
            {Symbol::start,       {Symbol::call, Symbol::EOS}},

            {Symbol::start,       {Symbol::assignment, Symbol::EOS, Symbol::start}},
            {Symbol::start,       {Symbol::function, Symbol::EXTENT, Symbol::start}},
            {Symbol::start,       {Symbol::keyword, Symbol::EOS, Symbol::start}},
            {Symbol::start,       {Symbol::call, Symbol::EOS, Symbol::start}},

 *
 *
 */

std::vector<ACC::Rule> ACC::data::getRules() {
    return { // vector
        {{Symbol::start, {Symbol::assignment, Symbol::EOS}}, [](auto children){
            return new ASTNode(AstOperator::SEQ, {process(children[0])});
        }},
        {{Symbol::start, {Symbol::keyword, Symbol::EOS}}, [](auto children){
            return new ASTNode(AstOperator::SEQ, {process(children[0])});
        }},
        {{Symbol::start, {Symbol::function, Symbol::EXTENT}}, [](auto children){
            return new ASTNode(AstOperator::SEQ, {process(children[0])});
        }},
        {{Symbol::start, {Symbol::call, Symbol::EOS}}, [](auto children){
            return new ASTNode(AstOperator::SEQ, {process(children[0])});
        }},


        {{Symbol::start, {Symbol::assignment, Symbol::EOS, Symbol::start}}, [](auto children){
            auto vec = {process(children[2]), process(children[0])};
            return new ASTNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::function, Symbol::EXTENT, Symbol::start}}, [](auto children){
            auto vec = {process(children[2]), process(children[0])};
            return new ASTNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::keyword, Symbol::EOS, Symbol::start}}, [](auto children){
            auto vec = {process(children[2]), process(children[0])};
            return new ASTNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::call, Symbol::EOS, Symbol::start}}, [](auto children){
            auto vec = {process(children[2]), process(children[0])};
            return new ASTNode(AstOperator::SEQ, vec);
        }},


        {{Symbol::function, {Symbol::FUNCTION, Symbol::DECL, Symbol::BRACKET, Symbol::paramsDecl, Symbol::BRACKET,
                                       Symbol::COLON, Symbol::INDENT, Symbol::start}}, [](auto children){

            std::vector<ASTNode*> vec;
            vec.push_back(new ASTNode(AstOperator::ID, dynamic_cast<DeclToken*>(children[1]->token)->sym));

            auto params = children[3];
            while(params != nullptr){
                vec.push_back(new ASTNode(AstOperator::ID, dynamic_cast<DeclToken*>(params->children[0]->token)->sym));
                if(params->children.size() == 3)
                    params = params->children[2];
                else
                    params = nullptr;
            }

            vec.push_back(process(children[7]));

            return new ASTNode(AstOperator::FUNCTION, vec);
        }},

        {{Symbol::call, {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET}}, [](auto children){

            std::vector<ASTNode*> vec;
            vec.push_back(new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym));

            ParseNode* params = children[2];
            while(params != nullptr){
                switch(params->children[0]->symbol) {
                    case (Symbol::ID):
                        vec.push_back(new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(params->children[0]->token)->sym));
                        break;
                    case (Symbol::LITERAL):
                        vec.push_back(new ASTNode(AstOperator::LITERAL, dynamic_cast<LiteralToken*>(params->children[0]->token)->literal));
                        break;

                    default:
                        throw std::runtime_error("Parameter List of a call, contains neither ID token, nor LITERAL token");
                }

                if(params->children.size() == 3)
                    params = params->children[2];
                else
                    params = nullptr;
            }

            return new ASTNode(AstOperator::CALL, vec);
        }},


        {{Symbol::call, {Symbol::ID, Symbol::BRACKET, Symbol::BRACKET}}, [](auto children){
           return new ASTNode(AstOperator::CALL,
                   {new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym)});
        }},



        {{Symbol::assignment, {Symbol::VAR, Symbol::DECL, Symbol::ASSIGN, Symbol::expr}}, [](auto children){
            auto vec = {new ASTNode(AstOperator::ID, dynamic_cast<DeclToken*>(children[1]->token)->sym),
                        process(children[3])};
            return new ASTNode(AstOperator::ASSIGN, vec);
        }},

        {{Symbol::keyword, {Symbol::PRINT, Symbol::ID}}, [](auto children){
            return new ASTNode(AstOperator::PRINT,
                    {new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[1]->token)->sym)});
        }},

        {{Symbol::keyword, {Symbol::EXIT, Symbol::LITERAL}}, [](auto children){
            return new ASTNode(AstOperator::EXIT,
                               {new ASTNode(AstOperator::LITERAL, dynamic_cast<LiteralToken*>(children[1]->token)->literal)});
        }},

        {{Symbol::keyword, {Symbol::RETURN, Symbol::LITERAL}}, [](auto children){
            return new ASTNode(AstOperator::RETURN,
                               {new ASTNode(AstOperator::LITERAL, dynamic_cast<LiteralToken*>(children[1]->token)->literal)});
        }},

        {{Symbol::keyword, {Symbol::RETURN, Symbol::ID}}, [](auto children){
            return new ASTNode(AstOperator::RETURN,
                               {new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[1]->token)->sym)});
        }},


        {{Symbol::expr, {Symbol::LITERAL}}, [](std::vector < ACC::ParseNode * > children) {
            return new ASTNode(AstOperator::LITERAL, dynamic_cast<LiteralToken*>(children[0]->token)->literal);
        }},

        {{Symbol::expr, {Symbol::ID}}, [](std::vector < ACC::ParseNode * > children) {
            return new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym);
        }},

         {{Symbol::expr, {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET}}, [](std::vector < ACC::ParseNode * > children){
             return process(children[1]);
         }},

         {{Symbol::expr, {Symbol::expr, Symbol::MATH_OPERATOR, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children){
             auto vec = {process(children[0]), process(children[2])};
             switch (dynamic_cast<MathOperatorToken*>(children[1]->token)->kind){
                 case MathOperators::PLUS:
                     return new ASTNode(AstOperator::PLUS, vec);
                 case MathOperators::MINUS:
                      return new ASTNode(AstOperator::MINUS, vec);
                 case MathOperators::MULTIPLICATION:
                     return new ASTNode(AstOperator::MULTIPLICATION, vec);
                 case MathOperators::DIVISION:
                     return new ASTNode(AstOperator::DIVISION, vec);
             }
         }}
    };
}