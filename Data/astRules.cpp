#include <Logger/Logger.h>
#include <astRules.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <AbstractSyntaxTree/process.h>
#include <AbstractSyntaxTree/ASTNode.h>
#include <Lexical/Tokens/MathOperatorToken.h>
#include <Parser/Production.h>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/SyscallToken.h>
#include <Lexical/Tokens/DeclToken.h>
#include <Lexical/Tokens/TypeToken.h>

std::vector<ACC::Rule> ACC::data::getRules() {
    return { // vector
        {{Symbol::start, {Symbol::assignment, Symbol::EOS}}, [](auto children, auto carry){
            return new ASTNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},
        {{Symbol::start, {Symbol::keyword, Symbol::EOS}}, [](auto children, auto carry){
            return new ASTNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},
        {{Symbol::start, {Symbol::function, Symbol::EXTENT}}, [](auto children, auto carry){
            return new ASTNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},
        {{Symbol::start, {Symbol::call, Symbol::EOS}}, [](auto children, auto carry){
            return new ASTNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},


        {{Symbol::start, {Symbol::assignment, Symbol::EOS, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[2], nullptr), process(children[0], nullptr)};
            return new ASTNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::function, Symbol::EXTENT, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[2], nullptr), process(children[0], nullptr)};
            return new ASTNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::keyword, Symbol::EOS, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[2], nullptr), process(children[0], nullptr)};
            return new ASTNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::call, Symbol::EOS, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[2], nullptr), process(children[0], nullptr)};
            return new ASTNode(AstOperator::SEQ, vec);
        }},


        {{Symbol::function, {Symbol::FUNCTION, Symbol::DECL, Symbol::BRACKET, Symbol::paramsDecl, Symbol::BRACKET,
                             Symbol::TYPE, Symbol::COLON, Symbol::INDENT, Symbol::start}}, [](auto children, auto carry){

            std::vector<ASTNode*> vec;
            vec.push_back(new ASTNode(AstOperator::ID, dynamic_cast<DeclToken*>(children[1]->token)->sym));

            vec.push_back(new ASTNode(AstOperator::TYPE_DEF,
                                      GeneralDataStore::create(dynamic_cast<TypeToken*>(children[5]->token)->typeId)));


            auto params = children[3];
            while(params != nullptr){
                auto paramsVec = {
                        new ASTNode(AstOperator::ID, dynamic_cast<DeclToken*>(params->children[0]->token)->sym),
                        new ASTNode(AstOperator::TYPE_DEF, GeneralDataStore::create(
                                dynamic_cast<TypeToken*>(params->children[1]->token)->typeId))

                };
                vec.push_back(new ASTNode(AstOperator::__CONTAINER, paramsVec));

                if(params->children.size() == 4)
                    params = params->children[3];
                else
                    params = nullptr;
            }

            vec.push_back(process(children[8], nullptr));

            return new ASTNode(AstOperator::FUNCTION, vec);
        }},

        {{Symbol::function, {Symbol::FUNCTION, Symbol::DECL, Symbol::BRACKET, Symbol::BRACKET, Symbol::TYPE,
                                    Symbol::COLON, Symbol::INDENT, Symbol::start}}, [](auto children, auto carry){

            std::vector<ASTNode*> vec;
            vec.push_back(new ASTNode(AstOperator::ID, dynamic_cast<DeclToken*>(children[1]->token)->sym));
            vec.push_back(new ASTNode(AstOperator::TYPE_DEF,
                    GeneralDataStore::create(dynamic_cast<TypeToken*>(children[4]->token)->typeId)));

            vec.push_back(process(children[7], nullptr));

            return new ASTNode(AstOperator::FUNCTION, vec);
        }},

        {{Symbol::call, {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET}}, [](auto children, auto carry){

            std::vector<ASTNode*> vec;
            vec.push_back(new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym));

            ParseNode* params = children[2];
            while(params != nullptr){
                vec.push_back(process(params->children[0], nullptr));
                if(params->children.size() == 3)
                    params = params->children[2];
                else
                    params = nullptr;
            }

            return new ASTNode(AstOperator::CALL, vec);
        }},


        {{Symbol::call, {Symbol::ID, Symbol::BRACKET, Symbol::BRACKET}}, [](auto children, auto carry){
            std::vector<ASTNode*> vec = {new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym)};
             return new ASTNode(AstOperator::CALL, vec);
        }},



        {{Symbol::assignment, {Symbol::VAR, Symbol::DECL, Symbol::TYPE, Symbol::ASSIGN, Symbol::expr}}, [](auto children, auto carry){
            GeneralDataStore store = GeneralDataStore::create(dynamic_cast<TypeToken*>(children[2]->token)->typeId);
            auto vec = {new ASTNode(AstOperator::ID, dynamic_cast<DeclToken*>(children[1]->token)->sym),
                        new ASTNode(AstOperator::TYPE_DEF, store),
                        process(children[4], nullptr)};
            return new ASTNode(AstOperator::ASSIGN, vec);
        }},

        {{Symbol::assignment, {Symbol::ID, Symbol::ASSIGN, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym),
                        process(children[2], nullptr)};
            return new ASTNode(AstOperator::REASSIGN, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)
                    ,process(children[7], nullptr), process(children[9], nullptr), process(children[11], nullptr),
                    process(children[13], nullptr)};
            return new ASTNode(AstOperator::SYSCALL, vec);
        }},

        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}},
         [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)
                    , process(children[7], nullptr), process(children[9], nullptr), process(children[11], nullptr)};
            return new ASTNode(AstOperator::SYSCALL, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)
                    , process(children[7], nullptr), process(children[9], nullptr)};
            return new ASTNode(AstOperator::SYSCALL, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)
                    , process(children[7], nullptr)};
            return new ASTNode(AstOperator::SYSCALL, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}},
         [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)};
            return new ASTNode(AstOperator::SYSCALL, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr)};
            return new ASTNode(AstOperator::SYSCALL, vec);
        }},

        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr)};
            return new ASTNode(AstOperator::SYSCALL, vec);
        }},

        {{Symbol::keyword, {Symbol::EXIT, Symbol::expr}}, [](auto children, auto carry){
            return new ASTNode(AstOperator::EXIT,
                               {process(children[1], nullptr)});
        }},

        {{Symbol::keyword, {Symbol::RETURN, Symbol::expr}}, [](auto children, auto carry){
            return new ASTNode(AstOperator::RETURN,
                               {process(children[1], nullptr)});
        }},
        {{Symbol::expr, {Symbol::ID, Symbol::BRACKET, Symbol::BRACKET}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
                return new ASTNode(AstOperator::CALL,
                                   {new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym)});
        }},

        {{Symbol::expr, {Symbol::ID, Symbol::BRACKET, Symbol::BRACKET, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            auto call = new ASTNode(AstOperator::CALL,
                               {new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym)});
            return process(children[3], call);
        }},

        {{Symbol::expr, {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            std::vector<ASTNode*> vec;
            vec.push_back(new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym));

            ParseNode* params = children[2];
            while(params != nullptr){
                vec.push_back(process(params->children[0], nullptr));
                if(params->children.size() == 3)
                    params = params->children[2];
                else
                    params = nullptr;
            }

            return new ASTNode(AstOperator::CALL, vec);
        }},

        {{Symbol::expr, {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            std::vector<ASTNode*> vec;
            vec.push_back(new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym));

            ParseNode* params = children[2];
            while(params != nullptr){
                vec.push_back(process(params->children[0], nullptr));
                if(params->children.size() == 3)
                    params = params->children[2];
                else
                    params = nullptr;
            }

            auto call = new ASTNode(AstOperator::CALL, vec);
            return process(children[4], call);
        }},

        {{Symbol::expr, {Symbol::LITERAL}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            auto asLiteralToken = dynamic_cast<LiteralToken*>(children[0]->token);
            return new ASTNode(AstOperator::LITERAL, asLiteralToken->literal, asLiteralToken->type);
        }},

        {{Symbol::expr, {Symbol::LITERAL, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            auto asLiteralToken = dynamic_cast<LiteralToken*>(children[0]->token);
            auto literal = new ASTNode(AstOperator::LITERAL, asLiteralToken->literal, asLiteralToken->type);
            return process(children[1], literal);
        }},

        {{Symbol::expr, {Symbol::ID}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            return new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym);
        }},

        {{Symbol::expr, {Symbol::ID, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            auto id = new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym);
            return process(children[1], id);
        }},

         {{Symbol::expr, {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET}}, [](std::vector < ACC::ParseNode * > children, auto carry){
             return process(children[1], nullptr);
         }},

        {{Symbol::expr, {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry){
            return process(children[3], process(children[1]));
        }},

         {{Symbol::expr, {Symbol::MATH_OPERATOR, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry){
             auto vec = {carry, process(children[1], nullptr)};
             switch (dynamic_cast<MathOperatorToken*>(children[0]->token)->kind){
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

/*
            {Symbol::expr,        {Symbol::LITERAL}},
            {Symbol::expr,        {Symbol::LITERAL, Symbol::expr}},

            {Symbol::expr,        {Symbol::ID}},
            {Symbol::expr,        {Symbol::ID, Symbol::expr}},

            {Symbol::expr,        {Symbol::ID,    Symbol::BRACKET, Symbol::BRACKET}},
            {Symbol::expr,        {Symbol::ID,    Symbol::BRACKET, Symbol::BRACKET, Symbol::expr}},

            {Symbol::expr,        {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET}},
            {Symbol::expr,        {Symbol::ID, Symbol::BRACKET, Symbol::paramsList, Symbol::BRACKET, Symbol::expr}},

            {Symbol::expr,        {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET}},
            {Symbol::expr,        {Symbol::BRACKET, Symbol::expr, Symbol::BRACKET, Symbol::expr}},

            {Symbol::expr,        {Symbol::MATH_OPERATOR, Symbol::expr}}
 *
 * */