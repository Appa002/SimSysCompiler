//
// Created by a_mod on 06.01.2019.
//

#include <Lexical/Tokens/WhileToken.h>
#include <Lexical/Tokens/TypeToken.h>
#include "LexicalAnalysis.h"
#include <fstream>
#include <iostream>
#include <Lexical/Tokens/EOSToken.h>
#include <Logger/Logger.h>

#include <Lexical/Tokens/LiteralToken.h>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/ClosedBracketToken.h>
#include <Lexical/Tokens/OpenBracketToken.h>
#include <Lexical/Tokens/SallocToken.h>
#include <Lexical/Tokens/ModuloToken.h>
#include <Lexical/Tokens/SyscallToken.h>
#include <Lexical/Tokens/AssignToken.h>
#include <Lexical/Tokens/DeclToken.h>
#include <Lexical/Tokens/ExitToken.h>
#include <Lexical/Tokens/IndentToken.h>
#include <Lexical/Tokens/FunctionToken.h>
#include <Lexical/Tokens/ForToken.h>
#include <Lexical/Tokens/ElifToken.h>
#include <Lexical/Tokens/ColonToken.h>
#include <Lexical/Tokens/ExtentToken.h>
#include <Lexical/Tokens/CommaToken.h>
#include <Lexical/Tokens/ReturnToken.h>
#include <General/builtinTypes.h>
#include <Lexical/Tokens/IfToken.h>
#include <Lexical/Tokens/ComparisionToken.h>
#include <Lexical/Tokens/NotToken.h>
#include <Lexical/Tokens/ElseToken.h>
#include <Lexical/Tokens/GoesToToken.h>
#include <Lexical/Tokens/PlusToken.h>
#include <Lexical/Tokens/StarToken.h>
#include <Lexical/Tokens/MinusToken.h>
#include <Lexical/Tokens/SlashToken.h>

bool contains(const std::string &str, std::vector<std::string> options){
    for(auto const & option : options){
        if(str == option)
            return true;
    }
    return false;
}

bool contains(char c, std::vector<std::string> options){
    for(auto const & option : options){
        if(c == option[0])
            return true;
    }
    return false;
}

void ACC::LexicalAnalysis::start(size_t pos, bool shallCheckIndent){
    if(pos >= document.size())
        return;

    std::vector<std::string> keyOptions = {
            "fn", "var", "exit", "syscall", "return", "if", "elif", "else", "while", "for", "*", "salloc", "import"
    };

    if(shallCheckIndent) {
        int newDepth = readUntilNextLine(pos);
        if (newDepth > depth){
            tokens.push_back(new IndentToken());
            indentList.push_back(newDepth);
        }
        else if (newDepth < depth){
            while( indentList.at(indentList.size() - 1) > newDepth  ){
                tokens.push_back(new ExtentToken());
                indentList.pop_back();
            }
            popScope();
        }
        depth = newDepth;
    }
    if(pos >= document.size())
        return;

    buffer += document.at(pos);
    if(contains(buffer, keyOptions)){

        if("fn" == buffer){
            tokens.push_back(new FunctionToken());
            buffer.clear();
            fn(pos + 1);
            return;
        }
        else if ("var" == buffer){
            tokens.push_back(new VarToken());
            buffer.clear();
            var(pos + 1);
            return;

        }else if ("exit" == buffer){
            tokens.push_back(new ExitToken());
            buffer.clear();
            exit(pos + 1);
            return;

        }else if ("syscall" == buffer) {
            tokens.push_back(new SyscallToken());
            buffer.clear();
            syscall(pos + 1);
            return;
        }else if ("return" == buffer){
            tokens.push_back(new ReturnToken());
            buffer.clear();
            ret(pos + 1);
            return;
        }else if("if" == buffer){
            tokens.push_back(new IfToken());
            buffer.clear();
            ifStmt(pos + 1);
            return;
        }else if("elif" == buffer){
            tokens.push_back(new ElifToken());
            buffer.clear();
            ifStmt(pos + 1);
            return;
        }else if("else" == buffer){
            tokens.push_back(new ElseToken());
            buffer.clear();
            elseStmt(pos + 1);
            return;
        }else if ("while" == buffer){
            tokens.push_back(new WhileToken());
            buffer.clear();
            whileStmt(pos + 1);
            return;
        }else if ("for" == buffer){
            tokens.push_back(new ForToken());
            buffer.clear();
            forStmt(pos + 1);
            return;
        }else if ("*" == buffer){
            tokens.push_back(new StarToken());
            buffer.clear();
            dereferencingAsignment(pos + 1);
            return;

        }
        else if ("salloc" == buffer){
            tokens.push_back(new Salloc());
            buffer.clear();
            salloc(pos + 1);
            return;
        }else if ("import" == buffer){
            buffer.clear();
            import(pos + 1);
            return;

        }
    }
    else if (isSymbol(buffer) && (document.size() - 1 == pos || contains(document.at(pos + 1),
            {"\"", ";", " ", "\n", "\r", "(", ")", "+", "-", "*", "/", ",", "=", "<", ">", "!", ":", "\'"}))) {

        tokens.push_back(new IdToken(buffer));
        auto sym = getSymbol(buffer);
        if(sym == Symbol::FUNCTION){
            buffer.clear();
            call(pos + 1);
        }else if(sym == Symbol::DECL){
            buffer.clear();
            assignment(pos + 1);
        }
        return;
    }
    else{
        if(pos < document.size())
            start(pos + 1);
        else
            return;
    }
}

void ACC::LexicalAnalysis::call(size_t pos){
    if(matchIgnoreW('(', pos))
        tokens.push_back(new OpenBracketToken());
    else
        throw std::runtime_error("Call must be followed by parameter list, at: " + std::to_string(pos));


    pos++;
    while(pos < document.size() && document.at(pos - 1) != ')'){
        try {
            expr(pos, {",", ")"});
        }catch (std::runtime_error& e){
            throw std::runtime_error("Expected expression in parameter list, at: " + std::to_string(pos) + "\n"
                                    "expression failed with: " + e.what());
        }

        if(pos >= document.size())
            throw std::runtime_error("Expected expression in parameter list, at: " + std::to_string(pos));


        if(document.at(pos) == ',')
            tokens.push_back(new CommaToken());
        buffer.clear();
        pos++;
    }

    tokens.push_back(new ClosedBracketToken());


    if(!matchIgnoreW(';', pos))
        throw std::runtime_error("Missing `;` after call statements, at: " + std::to_string(pos));

    tokens.push_back(new EOSToken());
    pos++;
    buffer.clear();
    start(pos, true);

}


void ACC::LexicalAnalysis::callExpr(size_t &pos) {
    buffer.clear();
    if(matchIgnoreW('(', pos))
        tokens.push_back(new OpenBracketToken());
    else
        throw std::runtime_error("Call must be followed by parameter list, at: " + std::to_string(pos));


    pos++;
    while(pos < document.size() && document.at(pos - 1) != ')'){
        try {
            expr(pos, {",", ")"});
        }catch (std::runtime_error& e){
            throw std::runtime_error("Expected expression in parameter list, at: " + std::to_string(pos) + "\n"
                                                                                                           "expression failed with: " + e.what());
        }

        if(pos >= document.size())
            throw std::runtime_error("Expected expression in parameter list, at: " + std::to_string(pos));


        if(document.at(pos) == ',')
            tokens.push_back(new CommaToken());
        buffer.clear();
        pos++;
    }

    tokens.push_back(new ClosedBracketToken());
    pos--;
}

void ACC::LexicalAnalysis::assignment(size_t pos) {
    if(!matchIgnoreW('=', pos))
        throw std::runtime_error("Assignment needs to be followed by an expression, at:" + std::to_string(pos));

    tokens.push_back(new AssignToken());

    pos++;
    expr(pos, {";"});

    if(!matchIgnoreW(';', pos))
        throw std::runtime_error("Missing ; at end of expression, at:" + std::to_string(pos));

    tokens.push_back(new EOSToken());

    start(pos + 1, true);
}

void ACC::LexicalAnalysis::ret(size_t pos) {
    readUntilNextLine(pos);

    try {
        expr(pos, {";"});
    }catch (std::runtime_error& e){
        throw std::runtime_error("Not an expression, at: " + std::to_string(pos) + "\n" + e.what());
    }

    readUntilNextLine(pos);

    if(!matchIgnoreW(';', pos))
        throw std::runtime_error("Missing `;` after print statements, at: " + std::to_string(pos));

    tokens.push_back(new EOSToken());
    pos++;
    buffer.clear();
    start(pos, true);
}

void ACC::LexicalAnalysis::var(size_t pos) {
    // var a = öflksajdflä;

    readUntilNextLine(pos);

    matchAsLongAs(pos,
                  [&](){return !contains(document.at(pos), {";", " ", ":", "\n", "\r", "(", ")", "+", "-", "*", "/"});},
                  [&](){
                      buffer += document.at(pos);
    });

    if(curScope->isSymbolInThisScope(buffer))
        throw std::runtime_error("Redefinition variable `"+ buffer +"`, at: " + std::to_string(pos));

    if(contains(buffer, { "fn", "var", "exit", "syscall", "return", "if", "elif", "else", "while", "for"}))
        throw std::runtime_error("Can't use keyword as variable name, at: " + std::to_string(pos));

    tokens.push_back(new DeclToken(buffer));
    emplaceSymbol(buffer, Symbol::DECL);

    if(!matchIgnoreW(':', pos))
        throw std::runtime_error("Variable declaration requires type, at: " + std::to_string(pos));

    buffer.clear();
    pos++;
    type(pos);

    readUntilNextLine(pos);
    if(document.at(pos) != '=')
        throw std::runtime_error("Can't declare variable without defining it, at: " + std::to_string(pos));

    tokens.push_back(new AssignToken());

    buffer.clear();
    pos++;
    expr(pos, {";"});


    if(document.at(pos) != ';')
        throw std::runtime_error("Expected ; at end of variable definition, at: " + std::to_string(pos));

    tokens.push_back(new EOSToken());
    buffer.clear();
    pos++;
    start(pos, true);
}

void ACC::LexicalAnalysis::type(size_t &pos) {
    buffer.clear();
    readUntilNextLine(pos);
    bool matched = matchAsLongAs(pos,
                                 [&](){return !contains(document.at(pos), {"<", ">",
                                     "[", "]", "\"", ";", " ", "=", "(", ")", "+", "-", "*", "/", ",", ":"});},
                                 [&](){
                                     buffer += document.at(pos);
    });
    if(!matched)
        throw std::runtime_error("Syntax error, at: " + std::to_string(pos));

    Type id;

    if(isType(buffer) == TypeId(0,0) && matchIgnoreW('<', pos)){
        pos++;
        readUntilNextLine(pos);
        std::string typeName;
        matched = matchAsLongAs(pos,
                [&](){return !contains(document.at(pos), {"<", ">",
                                                          "[", "]", "\"", ";", " ", "=", "(", ")", "+", "-", "*", "/", ",", ":"});},
                [&](){
                    typeName += document.at(pos);
        });

        if(!matched)
            throw std::runtime_error("Syntax error, at: " + std::to_string(pos));
        pos++;

        if(buffer == "ptr"){
            if(isType(typeName) != TypeId(0, 0))
                id = Type(BuiltIns::ptrType, isType(typeName));
            else
                throw std::runtime_error("Not a type " + typeName);

        }
    }else
        id = isType(buffer);

    if(id.getId() == 0)
        throw std::runtime_error("Unknown type, at: " + std::to_string(pos));

    tokens.push_back(new TypeToken(buffer, id));
}

void ACC::LexicalAnalysis::expr(size_t& pos, std::vector<std::string> exitTokens) {
    while(!contains((readUntilNextLine(pos), document.at(pos)), exitTokens)){
        bool matched = matchAsLongAs(pos,
                      [&](){return !contains(document.at(pos), {"\"", ";", " ", "\n", "\r", "(", ")", "+", "-", "*", "/", ",", "=",
                                                                "<", ">", "!", ":", "\'", "%"});},
                      [&](){
                          buffer += document.at(pos);
        });

        if(matched)
            pos--;


        if(isNumber(buffer))
            tokens.push_back(new LiteralToken(std::stoul(buffer), Type(BuiltIns::numType)));

        else if (pos + 1 < document.size() && document.at(pos) == '!' && document.at(pos + 1) == '=') {
            tokens.push_back(new ComparisionToken(ComparisionTokenKind::NotEqual));
            pos++;
        }

        else if (pos + 1 < document.size() && document.at(pos) == '<' && document.at(pos + 1) == '='){
            tokens.push_back(new ComparisionToken(ComparisionTokenKind::LessEqual));
            pos++;
        }

        else if (pos + 1 < document.size() && document.at(pos) == '>' && document.at(pos + 1) == '='){
            tokens.push_back(new ComparisionToken(ComparisionTokenKind::GreaterEqual));
            pos++;
        }


        else if (pos + 1 < document.size() && document.at(pos) == '=' && document.at(pos + 1) == '='){
            tokens.push_back(new ComparisionToken(ComparisionTokenKind::Equal));
            pos++;
        }

        else if (document.at(pos) == '!')
            tokens.push_back(new NotToken());

        else if (document.at(pos) == '%')
            tokens.push_back(new ModuloToken());

        else if(document.at(pos) == '<')
            tokens.push_back(new ComparisionToken(ComparisionTokenKind::Less));

        else if(document.at(pos) == '>')
            tokens.push_back(new ComparisionToken(ComparisionTokenKind::Greater));

        else if(document.at(pos) == '"')
            tokens.push_back(new LiteralToken(parseStringLiteral(pos), Type(BuiltIns::ptrType, BuiltIns::charType)));
        else if(document.at(pos) == '\''){
            if(document.at(pos + 1) == '\\'){
                char other = document.at(pos + 2);
                if(other == 'n')
                    tokens.push_back(new LiteralToken('\n', Type(BuiltIns::charType)));
                else if(other == '\\')
                    tokens.push_back(new LiteralToken('\\', Type(BuiltIns::charType)));
                else if(other == 'r')
                    tokens.push_back(new LiteralToken('\r', Type(BuiltIns::charType)));
                else if(other == '"')
                    tokens.push_back(new LiteralToken('\"', Type(BuiltIns::charType)));
                else if(other == 'a')
                    tokens.push_back(new LiteralToken('\a', Type(BuiltIns::charType)));
                else if(other == '\'')
                    tokens.push_back(new LiteralToken('\'', Type(BuiltIns::charType)));
                pos += 3;
            }else {
                tokens.push_back(new LiteralToken(document.at(pos + 1), Type(BuiltIns::charType)));
                pos += 2;
            }
        }
        else if (isSymbol(buffer)){
            tokens.push_back(new IdToken(buffer));
            if(getSymbol(buffer) == Symbol::FUNCTION){
                pos++;
                callExpr(pos);
            }
        }
        else if (document.at(pos) == '(')
            tokens.push_back(new OpenBracketToken());
        else if (document.at(pos) == ')')
            tokens.push_back(new ClosedBracketToken());
        else if (document.at(pos) == '+')
            tokens.push_back(new PlusToken());
        else if (document.at(pos) == '-')
            tokens.push_back(new MinusToken());
        else if (document.at(pos) == '*')
            tokens.push_back(new StarToken());
        else if (document.at(pos) == '/')
            tokens.push_back(new SlashToken());
        else if (document.at(pos) == ',')
            tokens.push_back(new CommaToken());
        else
            throw std::runtime_error("Unknown symbol `"+buffer+"`, at: " + std::to_string(pos));

        buffer.clear();
        if(pos + 1 < document.size()){
            pos++;
        }else
            throw std::runtime_error("Expected ; at end of expression, at: " + std::to_string(pos));
    }
}

void ACC::LexicalAnalysis::fn(size_t pos){
    skipAll(' ', pos);

    matchAsLongAs(pos,
            [&](){return !contains(document.at(pos), {"(", " "});},
            [&](){
        buffer += document.at(pos);
    });

    tokens.push_back(new DeclToken(buffer));
    emplaceSymbol(buffer, Symbol::FUNCTION);

    buffer.clear();
    if(matchIgnoreW('(', pos))
        tokens.push_back(new OpenBracketToken());
    else
        throw std::runtime_error("Expected parameter list after function declaration; missing `(`, at: " + std::to_string(pos));

    pushScope();
    pos++;
    while(pos < document.size() && document.at(pos - 1) != ')'){
        while(pos < document.size()  && !contains(document.at(pos), {":", "," ,")"})){
            if(document.at(pos) == ' '){
                ++pos;
                continue;
            }

            buffer += document.at(pos);
            ++pos;
        }
        if(pos >= document.size())
            throw std::runtime_error("Expected declaration in parameter list, at: " + std::to_string(pos));

        if(!buffer.empty()){
            if(curScope->isSymbolInThisScope(buffer))
                throw std::runtime_error("Redeclaration of variable, at: " + std::to_string(pos));

            if(contains(buffer, {"fn", "var", "exit", "syscall", "return", "if"}))
                throw std::runtime_error("Can't use keyword as variable name, at: " + std::to_string(pos));

            tokens.push_back(new DeclToken(buffer));
            emplaceSymbol(buffer, Symbol::DECL);
            pos++;
            type(pos);
        }

        if(document.at(pos) == ',')
            tokens.push_back(new CommaToken());
        buffer.clear();
        pos++;
    }
    if(pos >= document.size())
        throw std::runtime_error("Expected declaration in parameter list, at: " + std::to_string(pos));


    tokens.push_back(new ClosedBracketToken());

    if(!matchIgnoreW(':', pos))
        throw std::runtime_error("Expected return type after function definition, at: " + std::to_string(pos));
    pos++;
    type(pos);

    if(matchIgnoreW(':', pos))
        tokens.push_back(new ColonToken());
    else
        throw std::runtime_error("Expected `:` in function definition at: " + std::to_string(pos));

    pos++;
    buffer.clear();
    start(pos, true);
}

void ACC::LexicalAnalysis::syscall(size_t pos) {
    expr(pos, {";"});

    readUntilNextLine(pos);

    if(!matchIgnoreW(';', pos))
        throw std::runtime_error("Missing `;` after print statements, at: " + std::to_string(pos));

    tokens.push_back(new EOSToken());
    pos++;
    buffer.clear();
    start(pos, true);
}

void ACC::LexicalAnalysis::exit(size_t pos) {
    readUntilNextLine(pos);

    try {
        expr(pos, {";"});
    }catch (std::runtime_error& e){
        throw std::runtime_error("Not an expression, at: " + std::to_string(pos) + "\n" + e.what());
    }

    readUntilNextLine(pos);

    if(!matchIgnoreW(';', pos))
        throw std::runtime_error("Missing `;` after exit statements, at: " + std::to_string(pos));

    tokens.push_back(new EOSToken());
    pos++;
    buffer.clear();
    start(pos, true);
}

ACC::LexicalAnalysis::LexicalAnalysis(std::string path){
    indentList.push_back(0);
    refCount++;
    std::ifstream fs;
    fs.open(path);
    this->document = std::string((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

    curScope = new ScopedSymbolTable<Symbol>();
    globalScope = curScope;

    // Built In types
    typesTable["num"] = BuiltIns::numType;
    typesTable["char"] = BuiltIns::charType;
    //
    // Built in Functions
    emplaceSymbol("char", Symbol::FUNCTION);
    emplaceSymbol("num", Symbol::FUNCTION);
    //
    LOG.createHeading("Original Input being Lexically Analysed:");
    LOG() << this->document << std::endl;
    start(0);
    postProcessDocument();

}

ACC::LexicalAnalysis::LexicalAnalysis(const ACC::LexicalAnalysis &other) : buffer(other.buffer), tokens(other.tokens),
document(other.document), depth(other.depth), refCount(other.refCount), typesTable(other.typesTable), curScope(other.curScope),
globalScope(other.globalScope){
    refCount++;
}



ACC::LexicalAnalysis::~LexicalAnalysis() {
    refCount--;
    if(refCount != 0)
        return;

    delete globalScope;

    if(!shallDeleteTokens)
        return;

    for(const auto& it : tokens)
        delete it;
}

void ACC::LexicalAnalysis::postProcessDocument() {
    for(size_t i = 1; i < indentList.size(); i++){
        tokens.push_back(new ExtentToken());
    }
}

void ACC::LexicalAnalysis::printToken() {
    LOG.createHeading("Tokens generated by the Lexical Analysis:");
    int prefix = 0;
    std::string out;
    for(auto token : tokens){
        if(token->id == Symbol::INDENT)
            prefix += 4;
        else if (token->id == Symbol::EXTENT)
            prefix -= 4;
        if (prefix < 0)
            out += "[[[NEGATIVE INDEX]]]" + token->getIdentifier()+ "\n";
        else
            out += std::string(prefix, ' ') + token->getIdentifier()+ "\n";
    }
    LOG() << out;
    std::ofstream os ("./debug.txt");
    os << out;
    os.close();
}

const std::vector<ACC::IToken *, std::allocator<ACC::IToken *>>::iterator ACC::LexicalAnalysis::begin() {
    return tokens.begin();
}

const std::vector<ACC::IToken *, std::allocator<ACC::IToken *>>::iterator ACC::LexicalAnalysis::end() {
    return tokens.end();
}

const std::vector<ACC::IToken *> &ACC::LexicalAnalysis::data() {
    return tokens;
}

bool ACC::LexicalAnalysis::isSymbol(std::string idf) {
    return curScope->isSymbol(idf);
}

bool ACC::LexicalAnalysis::isNumber(char c) {
    return (int)c >= 48 && (int)c <=57;
}

bool ACC::LexicalAnalysis::isNumber(std::string str) {
    if(str.empty())
        return false;
    for(auto const & c : str)
        if(!isNumber(c))
            return false;
    return true;
}

bool ACC::LexicalAnalysis::matchIgnoreW(char c, size_t& pos){
    while(document.at(pos) == ' '){
        pos++;
        if(pos >= document.size())
            return false;
    }

    return document.at(pos) == c;
}

void ACC::LexicalAnalysis::skipAll(char c, size_t& pos) {
    while(pos < document.size() && document.at(pos) == c)
        pos++;
}

int ACC::LexicalAnalysis::readUntilNextLine(size_t& pos){
    if(pos >= document.size())
        return 0;

    bool shallCount = false;
    int newGap = 0;



    while(contains(document.at(pos), {" ", "\n", "\r"})){
        if(document.at(pos) == '\n'){
            shallCount = true;
            newGap = 0;
        }else if(document.at(pos) == ' ')
            newGap++;
        ++pos;
        if(pos >= document.size())
            return 0;
    }
    return newGap;
}

bool
ACC::LexicalAnalysis::matchAsLongAs(size_t &pos, std::function<bool(void)> condition, std::function<void(void)> body) {
    bool b = false;
    while(condition()){
        body();
        if(pos + 1  >= document.size())
            return false;
        else
            pos++;
        b = true;
    }
    return b;
}

std::string ACC::LexicalAnalysis::parseStringLiteral(size_t &pos) {
    readUntilNextLine(pos);
    if(document.at(pos) != '"')
        throw std::runtime_error("String literal not starting with `\"`");

    std::string buffer;

    pos++;
    bool valid = matchAsLongAs(pos,
            [&](){return document.at(pos) != '"';},
            [&](){
        if(document.at(pos) == '\\'){
            pos++;
            if(document.at(pos) == 'n')
                buffer += '\n';
            else if(document.at(pos) == '\\')
                buffer += '\\';
            else if(document.at(pos) == 'r')
                buffer += '\r';
            else if(document.at(pos) == '"')
                buffer += '"';
            else if(document.at(pos) == 'a')
                buffer += '\a';
            else if(document.at(pos) == '\'')
                buffer += '\'';
            else
                throw std::runtime_error("Escape sequence with out escapee, at: " + std::to_string(pos));

        }else
            buffer += document.at(pos);
    });

    if(!valid)
        throw std::runtime_error("Invalid string, at: " + std::to_string(pos));

    if(document.at(pos) != '"')
        throw std::runtime_error("String literal not ending with `\"`, at:" + std::to_string(pos));

    return buffer;
}

ACC::TypeId ACC::LexicalAnalysis::isType(std::string str) {
    if (typesTable.find(str) != typesTable.cend())
        return typesTable.at(str);
    return TypeId(0, 0);
}

void ACC::LexicalAnalysis::emplaceSymbol(std::string idf, ACC::Symbol symbol) {
    curScope->symbolTable[idf] = symbol;
}

void ACC::LexicalAnalysis::popScope() {
    auto old = curScope;
    curScope->prev->next = nullptr;
    curScope = curScope->prev;
    delete old;
}

void ACC::LexicalAnalysis::pushScope() {
    curScope = new ScopedSymbolTable<Symbol>(curScope);
}

ACC::Symbol ACC::LexicalAnalysis::getSymbol(std::string sym) {
    return curScope->getSymbol(sym);
}

void ACC::LexicalAnalysis::ifStmt(size_t pos) {
    pos++;
    expr(pos, {":"});
    if(!matchIgnoreW(':', pos))
        throw std::runtime_error("Expected block after if, at: " + std::to_string(pos));

    pos++;

    tokens.push_back(new ColonToken());
    pushScope();
    start(pos + 1, true);
}

void ACC::LexicalAnalysis::elseStmt(size_t pos) {
    if(!matchIgnoreW(':', pos))
        throw std::runtime_error("Else statements needs to be followed by a colon, at: " + std::to_string(pos));
    tokens.push_back(new ColonToken());
    pushScope();
    start(pos + 1, true);
}

void ACC::LexicalAnalysis::whileStmt(size_t pos) {
    pos++;
    expr(pos, {":"});
    if(!matchIgnoreW(':', pos))
        throw std::runtime_error("While loop requires block, at: " + std::to_string(pos));
    tokens.push_back(new ColonToken);
    pushScope();
    start(pos + 1, true);
}

void ACC::LexicalAnalysis::forStmt(size_t pos) {
    pos++;
    // match ID
    buffer.clear();
    readUntilNextLine(pos);
    matchAsLongAs(pos, [&](){return !contains(document.at(pos), {";", " ", ":", "\n", "\r", "(", ")", "+", "-", "*", "/"});},
            [&](){
        buffer += document.at(pos);
    });

    if(!curScope->isSymbolInThisScope(buffer))
        throw std::runtime_error("Unknown variable `"+ buffer +"`, at: " + std::to_string(pos));

    tokens.push_back(new IdToken(buffer));

    // match `->`
    readUntilNextLine(pos);
    if(!(document.at(pos) == '-' && document.at(pos + 1) == '>'))
        throw std::runtime_error("In for loop; variable goes to where?, at: " + std::to_string(pos));
    pos += 2;
    tokens.push_back(new GoesToToken());

    // match expr

    buffer.clear();
    expr(pos, {":"});
    if(!matchIgnoreW(':', pos))
        throw std::runtime_error("Expected block, at: " + std::to_string(pos));

    tokens.push_back(new ColonToken());

    pushScope();
    start(pos + 1, true);
}

void ACC::LexicalAnalysis::dereferencingAsignment(size_t pos) {
    expr(pos, {"="});
    if(!matchIgnoreW('=', pos))
        throw std::runtime_error("Expected expression, at: " + std::to_string(pos));
    tokens.push_back(new AssignToken());
    pos++;
    expr(pos, {";"});
    if(!matchIgnoreW(';', pos))
        throw std::runtime_error("Missing Semicolon, at: " + std::to_string(pos));
    tokens.push_back(new EOSToken);
    start(pos + 1, true);
}

void ACC::LexicalAnalysis::salloc(size_t pos) {
    expr(pos, {","});
    if(!matchIgnoreW(',', pos))
        throw std::runtime_error("Missing second argument, at: " + std::to_string(pos));

    tokens.push_back(new CommaToken());
    pos++;

    readUntilNextLine(pos);

    std::string buffer;
    matchAsLongAs(pos, [&](){return !contains(document.at(pos), {";", " ", ":", "\n", "\r", "(", ")", "+", "-", "*", "/"});},
                  [&](){
                      buffer += document.at(pos);
                  });

    if(!curScope->isSymbolInThisScope(buffer))
        throw std::runtime_error("Unknown variable `"+ buffer +"`, at: " + std::to_string(pos));

    tokens.push_back(new IdToken(buffer));

    if(!matchIgnoreW(';', pos))
        throw std::runtime_error("Missing Semicolon, at: " + std::to_string(pos));
    tokens.push_back(new EOSToken);

    start(pos + 1, true);
}

void ACC::LexicalAnalysis::import(size_t pos) {

    if(!matchIgnoreW('"', pos))
        throw std::runtime_error("Missing path after import statement, at: " + std::to_string(pos));


    std::string path = parseStringLiteral(pos);
    pos++;

    if(!matchIgnoreW(';', pos))
        throw std::runtime_error("Missing `;` after import statement, at: " + std::to_string(pos));

    auto l = LexicalAnalysis(path);
    integrateLexicalAnalysis(*this, l);
    l.dontAutoDeleteTokens();

    pos++;
    buffer.clear();
    start(pos, true);

}

void ACC::integrateLexicalAnalysis(ACC::LexicalAnalysis &subject, const ACC::LexicalAnalysis &other) {
    for (auto const & sym : other.globalScope->symbolTable){
        if(subject.globalScope->symbolTable.find(sym.first) != subject.globalScope->symbolTable.cend())
            throw std::runtime_error("Variable redefinition.");
        subject.globalScope->symbolTable[sym.first] = sym.second;
    }

    for (auto const & type : other.typesTable){
        if(subject.typesTable.find(type.first) == subject.typesTable.cend())
            subject.typesTable[type.first] = type.second;
    }

    subject.tokens.insert(subject.tokens.begin(), other.tokens.begin(), other.tokens.end());
}

void ACC::LexicalAnalysis::dontAutoDeleteTokens(bool b) {
    shallDeleteTokens = !b;
}

void ACC::LexicalAnalysis::addZeroExit() {
    tokens.push_back(new ExitToken());
    tokens.push_back(new LiteralToken((uint64_t)0, Type(BuiltIns::numType)));
    tokens.push_back(new EOSToken);
}

