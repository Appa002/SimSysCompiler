#include <Logger/Logger.h>
#include <astRules.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <AbstractSyntaxTree/process.h>
#include <AbstractSyntaxTree/ASTNode.h>
#include <General/builtinTypes.h>
#include <Parser/Production.h>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/SyscallToken.h>
#include <Lexical/Tokens/DeclToken.h>
#include <Lexical/Tokens/TypeToken.h>
#include <Lexical/Tokens/ComparisionToken.h>
#include <AbstractSyntaxTree/ASTNodes/SeqNode.h>
#include <AbstractSyntaxTree/ASTNodes/IfConstructNode.h>
#include <AbstractSyntaxTree/ASTNodes/WhileNode.h>
#include <AbstractSyntaxTree/ASTNodes/ForNode.h>
#include <AbstractSyntaxTree/ASTNodes/IdNode.h>
#include <AbstractSyntaxTree/ASTNodes/FunctionNode.h>
#include <AbstractSyntaxTree/ASTNodes/CallNode.h>
#include <AbstractSyntaxTree/ASTNodes/SallocNode.h>
#include <AbstractSyntaxTree/ASTNodes/AssignNode.h>
#include <AbstractSyntaxTree/ASTNodes/ReassignNode.h>
#include <AbstractSyntaxTree/ASTNodes/SyscallNode.h>
#include <AbstractSyntaxTree/ASTNodes/ExitNode.h>
#include <AbstractSyntaxTree/ASTNodes/ReturnNode.h>
#include <AbstractSyntaxTree/ASTNodes/LiteralNode.h>
#include <AbstractSyntaxTree/ASTNodes/AddNode.h>
#include <AbstractSyntaxTree/ASTNodes/SubtractNode.h>
#include <AbstractSyntaxTree/ASTNodes/MultiplicationNode.h>
#include <AbstractSyntaxTree/ASTNodes/DivisionNode.h>
#include <AbstractSyntaxTree/ASTNodes/ComparisionNode.h>
#include <AbstractSyntaxTree/ASTNodes/NotNode.h>
#include <AbstractSyntaxTree/ASTNodes/PtrAssignmentNode.h>
#include <AbstractSyntaxTree/ASTNodes/ModuloNode.h>
#include <Lexical/Tokens/SallocToken.h>
#include <AbstractSyntaxTree/ASTNodes/DereferenceNode.h>
#include <Lexical/Tokens/TextToken.h>

std::vector<ACC::Rule> ACC::data::getRules() {
    return { // vector
        {{Symbol::start, {Symbol::ptr_assign}}, [](auto children, auto carry){
            return new SeqNode(AstOperator::SEQ, {process(children[0], nullptr)});

        }},
        {{Symbol::start, {Symbol::assignment, Symbol::EOS}}, [](auto children, auto carry){
            return new SeqNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},
        {{Symbol::start, {Symbol::keyword, Symbol::EOS}}, [](auto children, auto carry){
            return new SeqNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},
        {{Symbol::start, {Symbol::function, Symbol::EXTENT}}, [](auto children, auto carry){
            return new SeqNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},
        {{Symbol::start, {Symbol::if_construct}}, [](auto children, auto carry){
            return new SeqNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},
        {{Symbol::start, {Symbol::for_construct}}, [](auto children, auto carry){
            return new SeqNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},
        {{Symbol::start, {Symbol::while_construct}}, [](auto children, auto carry){
            return new SeqNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},
        {{Symbol::start, {Symbol::call, Symbol::EOS}}, [](auto children, auto carry){
            return new SeqNode(AstOperator::SEQ, {process(children[0], nullptr)});
        }},


        {{Symbol::start, {Symbol::assignment, Symbol::EOS, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[2], nullptr), process(children[0], nullptr)};
            return new SeqNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::function, Symbol::EXTENT, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[2], nullptr), process(children[0], nullptr)};
            return new SeqNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::if_construct, Symbol::start}}, [](auto children, auto carry){
                auto vec = {process(children[1], nullptr), process(children[0], nullptr)};
                return new SeqNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::ptr_assign, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[0], nullptr)};
            return new SeqNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::while_construct, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[0], nullptr)};
            return new SeqNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::for_construct, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[0], nullptr)};
            return new SeqNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::keyword, Symbol::EOS, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[2], nullptr), process(children[0], nullptr)};
            return new SeqNode(AstOperator::SEQ, vec);
        }},
        {{Symbol::start, {Symbol::call, Symbol::EOS, Symbol::start}}, [](auto children, auto carry){
            auto vec = {process(children[2], nullptr), process(children[0], nullptr)};
            return new SeqNode(AstOperator::SEQ, vec);
        }},

        {{Symbol::ptr_assign, {Symbol::expr, Symbol::ASSIGN, Symbol::expr, Symbol::EOS}}, [](auto children, auto carry){
            auto vec = {process(children[0]->children[1], nullptr), process(children[2], nullptr)};
            return new PtrAssignmentNode(AstOperator::PTR_ASSIGN, vec);
        }},


        {{Symbol::if_construct, {Symbol::IF, Symbol::expr, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[4], nullptr)};
            return new IfConstructNode(AstOperator::IF_CONSTRUCT, {new ASTNode(AstOperator::IF, vec)});
        }},

        {{Symbol::while_construct, {Symbol::WHILE, Symbol::expr, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[4], nullptr)};
            return new WhileNode(AstOperator::WHILE, vec);
        }},

        {{Symbol::if_construct, {Symbol::IF, Symbol::expr, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT, Symbol::elseIf_construct}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[4], nullptr)};
            auto node = new IfConstructNode(AstOperator::IF_CONSTRUCT, {new ASTNode(AstOperator::IF, vec)});

            process(children[6], node);
            return node;
        }},

        {{Symbol::if_construct, {Symbol::IF, Symbol::expr, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT, Symbol::elseIf_construct, Symbol::else_construct}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[4], nullptr)};
            auto node = new IfConstructNode(AstOperator::IF_CONSTRUCT, {new ASTNode(AstOperator::IF, vec)});

            process(children[6], node);

            node->children.push_back(process(children[7], nullptr));

            return node;
        }},

        {{Symbol::if_construct, {Symbol::IF, Symbol::expr, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT, Symbol::else_construct}}, [](auto children, auto carry){
            auto ifVec = {process(children[1], nullptr), process(children[4], nullptr)};
            auto constructVec = {new ASTNode(AstOperator::IF, ifVec), process(children[6], nullptr)};
            return new IfConstructNode(AstOperator::IF_CONSTRUCT, constructVec);

        }},

        {{Symbol::elseIf_construct, {Symbol::ELIF, Symbol::expr, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[4], nullptr)};
            carry->children.push_back(new ASTNode(AstOperator::ELIF, vec));
            return nullptr;
        }},

        {{Symbol::elseIf_construct, {Symbol::ELIF, Symbol::expr, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT, Symbol::elseIf_construct}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[4], nullptr)};
            carry->children.push_back(new ASTNode(AstOperator::ELIF, vec));
            process(children[6], carry);
            return nullptr;
        }},

        {{Symbol::else_construct, {Symbol::ELSE, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT}}, [](auto children, auto carry){
            auto vec = {process(children[3], nullptr)};
            return new ASTNode(AstOperator::ELSE, vec);

        }},

        {{Symbol::for_construct, {Symbol::FOR, Symbol::TEXT, Symbol::ARROW, Symbol::expr, Symbol::COLON, Symbol::INDENT, Symbol::start, Symbol::EXTENT}}, [](auto children, auto carry){
            std::vector<ASTNode*> vec = {
                    new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[1]->token)->data),
                    process(children[3], nullptr),
                    process(children[6], nullptr)};
            return new ForNode(AstOperator::FOR, vec);

        }},


        {{Symbol::function, {Symbol::FUNCTION, Symbol::TEXT, Symbol::OPEN_BRACKET, Symbol::paramsDecl, Symbol::CLOSED_BRACKET,
                             Symbol::ARROW, Symbol::type, Symbol::COLON, Symbol::INDENT, Symbol::start}}, [](auto children, auto carry){

            std::vector<ASTNode*> vec;
            vec.push_back(new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[1]->token)->data));

            vec.push_back(process(children[6]));

            auto params = children[3];
            while(params != nullptr){
                std::vector<ASTNode*> paramsVec = {
                        new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(params->children[0]->token)->data),
                        process(params->children[2])
                };
                vec.push_back(new ASTNode(AstOperator::__CONTAINER, paramsVec));

                if(params->children.size() == 4)
                    params = params->children[3];
                else
                    params = nullptr;
            }

            vec.push_back(process(children[9], nullptr));

            return new FunctionNode(AstOperator::FUNCTION, vec);
        }},

        {{Symbol::function, {Symbol::FUNCTION, Symbol::TEXT, Symbol::OPEN_BRACKET, Symbol::CLOSED_BRACKET, Symbol::ARROW, Symbol::type,
                                    Symbol::COLON, Symbol::INDENT, Symbol::start}}, [](auto children, auto carry){

            std::vector<ASTNode*> vec;
            vec.push_back(new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[1]->token)->data));
            vec.push_back(process(children[5]));

            vec.push_back(process(children[8], nullptr));

            return new FunctionNode(AstOperator::FUNCTION, vec);
        }},

        {{Symbol::call, {Symbol::TEXT, Symbol::OPEN_BRACKET, Symbol::paramsList, Symbol::CLOSED_BRACKET}}, [](auto children, auto carry){

            std::vector<ASTNode*> vec;
            vec.push_back(new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[0]->token)->data));

            ParseNode* params = children[2];
            while(params != nullptr){
                vec.push_back(process(params->children[0], nullptr));
                if(params->children.size() == 3)
                    params = params->children[2];
                else
                    params = nullptr;
            }

            return new CallNode(AstOperator::CALL, vec);
        }},


        {{Symbol::call, {Symbol::ID, Symbol::OPEN_BRACKET, Symbol::CLOSED_BRACKET}}, [](auto children, auto carry){
            std::vector<ASTNode*> vec = {new ASTNode(AstOperator::ID, dynamic_cast<IdToken*>(children[0]->token)->sym)};
             return new CallNode(AstOperator::CALL, vec);
        }},


        {{Symbol::type, {Symbol::TEXT, Symbol::CMP, Symbol::TEXT, Symbol::CMP}}, [](auto children, auto carry){
            std::string str = dynamic_cast<TextToken*>(children[2]->token)->data;
            Type t;
            if(str == "num"){
                t = Type(BuiltIns::ptrType, BuiltIns::numType);
            } else if(str == "char"){
                t = Type(BuiltIns::ptrType, BuiltIns::charType);
            }

            return new ASTNode(AstOperator::TYPE_DEF, GeneralDataStore::create(t));
        }},

        {{Symbol::type, {Symbol::TEXT}}, [](auto children, auto carry){
            std::string str = dynamic_cast<TextToken*>(children[0]->token)->data;
            Type t;
            if(str == "num"){
                t = Type(BuiltIns::numType);
            } else if(str == "char"){
                t = Type(BuiltIns::charType);
            }

            return new ASTNode(AstOperator::TYPE_DEF, GeneralDataStore::create(t));
        }},


        {{Symbol::assignment, {Symbol::VAR, Symbol::TEXT, Symbol::COLON, Symbol::type, Symbol::ASSIGN, Symbol::expr}}, [](auto children, auto carry){
            std::vector<ASTNode*> vec = {
                        new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[1]->token)->data),
                        process(children[3]),
                        process(children[5], nullptr)};
            return new AssignNode(AstOperator::ASSIGN, vec);
        }},

        {{Symbol::assignment, {Symbol::TEXT, Symbol::ASSIGN, Symbol::expr}}, [](auto children, auto carry){
            std::vector<ASTNode*> vec = {new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[0]->token)->data),
                        process(children[2], nullptr)};
            return new ReassignNode(AstOperator::REASSIGN, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)
                    ,process(children[7], nullptr), process(children[9], nullptr), process(children[11], nullptr),
                    process(children[13], nullptr)};
            return new SyscallNode(AstOperator::SYSCALL, vec);
        }},

        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}},
         [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)
                    , process(children[7], nullptr), process(children[9], nullptr), process(children[11], nullptr)};
            return new SyscallNode(AstOperator::SYSCALL, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)
                    , process(children[7], nullptr), process(children[9], nullptr)};
            return new SyscallNode(AstOperator::SYSCALL, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr,
                            Symbol::COMMA, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)
                    , process(children[7], nullptr)};
            return new SyscallNode(AstOperator::SYSCALL, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr, Symbol::COMMA, Symbol::expr}},
         [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr), process(children[5], nullptr)};
            return new SyscallNode(AstOperator::SYSCALL, vec);
        }},


        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr, Symbol::COMMA, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr), process(children[3], nullptr)};
            return new SyscallNode(AstOperator::SYSCALL, vec);
        }},

        {{Symbol::keyword, {Symbol::SYSCALL, Symbol::expr}}, [](auto children, auto carry){
            auto vec = {process(children[1], nullptr)};
            return new SyscallNode(AstOperator::SYSCALL, vec);
        }},

        {{Symbol::keyword, {Symbol::EXIT, Symbol::expr}}, [](auto children, auto carry){
            return new ExitNode(AstOperator::EXIT,
                               {process(children[1], nullptr)});
        }},

        {{Symbol::keyword, {Symbol::RETURN, Symbol::expr}}, [](auto children, auto carry){
            return new ReturnNode(AstOperator::RETURN,
                               {process(children[1], nullptr)});
        }},

        {{Symbol::keyword, {Symbol::SALLOC, Symbol::expr, Symbol::COMMA, Symbol::TEXT}}, [](auto children, auto carry){
            std::vector<ASTNode*> vec = {process(children[1], nullptr),
                        new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[3]->token)->data)};
            return new SallocNode(AstOperator::SALLOC, vec);
        }},

        {{Symbol::expr, {Symbol::TEXT, Symbol::OPEN_BRACKET, Symbol::CLOSED_BRACKET}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
                return new CallNode(AstOperator::CALL,
                                   {new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[0]->token)->data)});
        }},

        {{Symbol::expr, {Symbol::TEXT, Symbol::OPEN_BRACKET, Symbol::CLOSED_BRACKET, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            auto call = new CallNode(AstOperator::CALL,
                               {new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[0]->token)->data)});
            return process(children[3], call);
        }},

        {{Symbol::expr, {Symbol::TEXT, Symbol::OPEN_BRACKET, Symbol::paramsList, Symbol::CLOSED_BRACKET}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            std::vector<ASTNode*> vec;
            vec.push_back(new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[0]->token)->data));

            ParseNode* params = children[2];
            while(params != nullptr){
                vec.push_back(process(params->children[0], nullptr));
                if(params->children.size() == 3)
                    params = params->children[2];
                else
                    params = nullptr;
            }

            return new CallNode(AstOperator::CALL, vec);
        }},

        {{Symbol::expr, {Symbol::TEXT, Symbol::OPEN_BRACKET, Symbol::paramsList, Symbol::CLOSED_BRACKET, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            std::vector<ASTNode*> vec;
            vec.push_back(new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[0]->token)->data));

            ParseNode* params = children[2];
            while(params != nullptr){
                vec.push_back(process(params->children[0], nullptr));
                if(params->children.size() == 3)
                    params = params->children[2];
                else
                    params = nullptr;
            }

            auto call = new CallNode(AstOperator::CALL, vec);
            return process(children[4], call);
        }},

        {{Symbol::expr, {Symbol::TEXT}}, [](std::vector < ACC::ParseNode * > children, auto carry) -> ASTNode*{
            std::string str = dynamic_cast<TextToken*>(children[0]->token)->data;

            bool isNumber = true;
            for(auto const & c : str){
                if(c < 48 || c > 57)
                    isNumber = false;
            }

            if(isNumber){
                GeneralDataStore value;
                value.storeT(std::stoul(str));
                Type t = Type(BuiltIns::numType);
                return new LiteralNode(AstOperator::LITERAL, value, t);

            } else {
                return new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[0]->token)->data);
            }

        }},

        {{Symbol::expr, {Symbol::TEXT, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            std::string str = dynamic_cast<TextToken*>(children[0]->token)->data;

            bool isNumber = true;
            for(auto const & c : str){
                if(c < 48 || c > 57)
                    isNumber = false;
            }

            if(isNumber){
                GeneralDataStore value;
                value.storeT(std::stoul(str));
                Type t = Type(BuiltIns::numType);
                auto literal = new LiteralNode(AstOperator::LITERAL, value, t);
                return process(children[1], literal);
            } else {
                return process(children[1], new IdNode(AstOperator::ID, dynamic_cast<TextToken*>(children[0]->token)->data));
            }

        }},

        {{Symbol::expr, {Symbol::DOUBLE_QUOTE, Symbol::TEXT, Symbol::DOUBLE_QUOTE}}, [](std::vector < ACC::ParseNode * > children, auto carry){
            std::string str = dynamic_cast<TextToken*>(children[1]->token)->data;

            GeneralDataStore value;
            Type t = Type(BuiltIns::ptrType, BuiltIns::charType);

            value.storeT(str);

            return new LiteralNode(AstOperator::LITERAL, value, t);
        }},


        {{Symbol::expr, {Symbol::QUOTE, Symbol::TEXT, Symbol::QUOTE}}, [](std::vector < ACC::ParseNode * > children, auto carry){
            std::string str = dynamic_cast<TextToken*>(children[1]->token)->data;

            GeneralDataStore value;
            Type t = Type(BuiltIns::charType);

            value.storeT(str[0]);

            return new LiteralNode(AstOperator::LITERAL, value, t);
        }},

         {{Symbol::expr, {Symbol::OPEN_BRACKET, Symbol::expr, Symbol::CLOSED_BRACKET}}, [](std::vector < ACC::ParseNode * > children, auto carry){
             return process(children[1], nullptr);
         }},

        {{Symbol::expr, {Symbol::OPEN_BRACKET, Symbol::expr, Symbol::CLOSED_BRACKET, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry){
            return process(children[3], process(children[1]));
        }},

         {{Symbol::expr, {Symbol::STAR, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) -> ASTNode*{
             if(carry != nullptr) // Its binary therefor multiplications
                 return new MultiplicationNode(AstOperator::MULTIPLICATION, {carry, process(children[1], nullptr)});

             // Its unary therefor dereference
             return new DereferenceNode(AstOperator::DEREFERENCE, {process(children[1], nullptr)});
         }},

        {{Symbol::expr, {Symbol::PLUS, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) -> ASTNode*{
            auto vec = {carry, process(children[1], nullptr)};
            return new AddNode(AstOperator::ADD, vec);
        }},

        {{Symbol::expr, {Symbol::MINUS, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) -> ASTNode*{
            auto vec = {carry, process(children[1], nullptr)};
            return new SubtractNode(AstOperator::SUBTRACT, vec);
        }},

        {{Symbol::expr, {Symbol::SLASH, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) -> ASTNode*{
            auto vec = {carry, process(children[1], nullptr)};
            return new DivisionNode(AstOperator::DIVISION, vec);
        }},

        {{Symbol::expr, {Symbol::MODULO, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) -> ASTNode*{
            auto vec = {carry, process(children[1], nullptr)};
            return new ModuloNode(AstOperator::DIVISION, vec);
        }},

        {{Symbol::expr, {Symbol::CMP, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) -> ASTNode*{
            auto vec = {carry, process(children[1], nullptr)};

            switch (dynamic_cast<ComparisionToken*>(children[0]->token)->kind){
                case ComparisionTokenKind::Equal:
                    return new ComparisionNode(AstOperator::EQUAL, vec, ComparisionType::EQ);
                case ComparisionTokenKind::NotEqual:
                    return new ComparisionNode(AstOperator::NOT_EQUAL, vec, ComparisionType::NEQ);
                case ComparisionTokenKind::Less:
                    return new ComparisionNode(AstOperator::LESS, vec, ComparisionType::LT);
                case ComparisionTokenKind::Greater:
                    return new ComparisionNode(AstOperator::GREATER, vec, ComparisionType::GT);
                case ComparisionTokenKind::LessEqual:
                    return new ComparisionNode(AstOperator::LESS_EQUAL, vec, ComparisionType::LET);
                case ComparisionTokenKind::GreaterEqual:
                    return new ComparisionNode(AstOperator::GREATER_EQUAL, vec, ComparisionType::GET);
            }
        }},

        {{Symbol::expr, {Symbol::NOT, Symbol::expr}}, [](std::vector < ACC::ParseNode * > children, auto carry) {
            return new NotNode(AstOperator::NOT, {process(children[1])});
        }},
    };
}