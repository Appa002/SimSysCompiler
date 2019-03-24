//
// Created by a_mod on 06.01.2019.
//

#include "LexicalAnalysis.h"
#include <fstream>
#include <iostream>
#include <Lexical/Tokens/EOSToken.h>
#include <errors.h>
#include <Logger/Logger.h>

#include <Lexical/Tokens/LiteralToken.h>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/BracketToken.h>
#include <Lexical/Tokens/MathOperatorToken.h>
#include <Lexical/Tokens/PrintToken.h>
#include <Lexical/Tokens/AssignToken.h>
#include <Lexical/Tokens/DeclToken.h>
#include <Lexical/Tokens/ExitToken.h>
#include <Lexical/Tokens/IndentToken.h>
#include <Lexical/Tokens/FunctionToken.h>
#include <Lexical/Tokens/ColonToken.h>
#include <Lexical/Tokens/ExtentToken.h>
#include <Lexical/Tokens/CommaToken.h>
#include <Lexical/Tokens/ReturnToken.h>

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
            "fn", "var", "exit", "print", "return"
    };

    if(shallCheckIndent) {
        int newDepth = readUntilNextLine(pos);
        if (newDepth > depth)
            tokens.push_back(new IndentToken());
        else if (newDepth < depth)
            tokens.push_back(new ExtentToken());
        depth = newDepth;
    }
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

        }else if ("print" == buffer) {
            tokens.push_back(new PrintToken());
            buffer.clear();
            print(pos + 1);
            return;
        }else if ("return" == buffer){
            tokens.push_back(new ReturnToken());
            buffer.clear();
            ret(pos + 1);
            return;
        }
    }else{
        if(pos < document.size())
            start(pos + 1);
        else
            return;
    }
}

void ACC::LexicalAnalysis::ret(size_t pos) {
    readUntilNextLine(pos);

    matchAsLongAs(pos,
                  [&](){return !contains(document.at(pos), {";", " ", "\n", "\r"});},
                  [&](){
                      buffer += document.at(pos);
                  });

    if(inTable(buffer))
        tokens.push_back(new IdToken(buffer));
    else{
        if(isNumber(buffer))
            tokens.push_back(new LiteralToken(buffer));
        else
            throw std::runtime_error("Unknown variable: `" + buffer + "`, at: " + std::to_string(pos));
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
                  [&](){return !contains(document.at(pos), {";", " ", "\n", "\r", "(", ")", "+", "-", "*", "/"});},
                  [&](){
                      buffer += document.at(pos);
    });

    if(inTable(buffer))
        throw std::runtime_error("Redefinition variable `"+ buffer +"`, at: " + std::to_string(pos));

    tokens.push_back(new DeclToken(buffer));
    table.emplace(buffer, Symbol::DECL);

    readUntilNextLine(pos);
    if(document.at(pos) != '=')
        throw std::runtime_error("Can't declare variable without defining it, at: " + std::to_string(pos));

    tokens.push_back(new AssignToken());

    buffer.clear();
    pos++;
    var_rhs(pos);
}

void ACC::LexicalAnalysis::var_rhs(size_t pos) {

    while((readUntilNextLine(pos), document.at(pos)) != ';'){
        bool matched = matchAsLongAs(pos,
                      [&](){return !contains(document.at(pos), {";", " ", "\n", "\r", "(", ")", "+", "-", "*", "/"});},
                      [&](){
                          buffer += document.at(pos);
        });

        if(matched)
            pos--;

        if(isNumber(buffer))
            tokens.push_back(new LiteralToken(buffer));
        else if (inTable(buffer))
            tokens.push_back(new IdToken(buffer));
        else if (document.at(pos) == '(')
            tokens.push_back(new BracketToken(BracketKind::OPEN));
        else if (document.at(pos) == ')')
            tokens.push_back(new BracketToken(BracketKind::CLOSED));
        else if (document.at(pos) == '+')
            tokens.push_back(new MathOperatorToken(MathOperators::PLUS));
        else if (document.at(pos) == '-')
            tokens.push_back(new MathOperatorToken(MathOperators::MINUS));
        else if (document.at(pos) == '*')
            tokens.push_back(new MathOperatorToken(MathOperators::MULTIPLICATION));
        else if (document.at(pos) == '/')
            tokens.push_back(new MathOperatorToken(MathOperators::DIVISION));
        else
            throw std::runtime_error("Unknown symbol `"+buffer+"`, at: " + std::to_string(pos));

        buffer.clear();
        if(pos + 1 < document.size()){
            pos++;
        }else
            throw std::runtime_error("Expected ; at end of variable definition, at: " + std::to_string(pos));
    }

    if(document.at(pos) != ';')
        throw std::runtime_error("Expected ; at end of variable definition, at: " + std::to_string(pos));

    tokens.push_back(new EOSToken());
    buffer.clear();
    pos++;
    start(pos, true);
}

void ACC::LexicalAnalysis::fn(size_t pos) {
    skipAll(' ', pos);

    matchAsLongAs(pos,
            [&](){return !contains(document.at(pos), {"(", " "});},
            [&](){
        buffer += document.at(pos);
    });

    tokens.push_back(new DeclToken(buffer));
    table.emplace(buffer, Symbol::FUNCTION);

    buffer.clear();

    if(matchIgnoreW('(', pos))
        tokens.push_back(new BracketToken(BracketKind::OPEN));
    else
        throw std::runtime_error("Expected parameter list after function declaration; missing `(`, at: " + std::to_string(pos));

    pos++;
    while(pos < document.size() && document.at(pos - 1) != ')'){
        while(pos < document.size()  && !contains(document.at(pos), {",", ")"})){
            if(document.at(pos) == ' '){
                ++pos;
                continue;
            }

            buffer += document.at(pos);
            ++pos;
        }
        if(pos >= document.size())
            throw std::runtime_error("Expected declaration in parameter list, at: " + std::to_string(pos));

        tokens.push_back(new DeclToken(buffer));
        table.emplace(buffer, Symbol::DECL);

        if(document.at(pos) == ',')
            tokens.push_back(new CommaToken());
        buffer.clear();
        pos++;
    }
    if(pos >= document.size())
        throw std::runtime_error("Expected declaration in parameter list, at: " + std::to_string(pos));


    tokens.push_back(new BracketToken(BracketKind::CLOSED));


    if(matchIgnoreW(':', pos))
        tokens.push_back(new ColonToken());
    else
        throw std::runtime_error("Expected `:` in function definition at: " + std::to_string(pos));

    pos++;
    buffer.clear();
    start(pos, true);
}

void ACC::LexicalAnalysis::print(size_t pos) {
    readUntilNextLine(pos);

    matchAsLongAs(pos,
                  [&](){return !contains(document.at(pos), {";", " ", "\n", "\r"});},
                  [&](){
                      buffer += document.at(pos);
    });

    if(inTable(buffer))
        tokens.push_back(new IdToken(buffer));
    else{
        if(isNumber(buffer))
            tokens.push_back(new LiteralToken(buffer));
        else
            throw std::runtime_error("Unknown variable: `" + buffer + "`, at: " + std::to_string(pos));
    }

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

    matchAsLongAs(pos,
                  [&](){return !contains(document.at(pos), {";", " ", "\n", "\r"});},
                  [&](){
                      buffer += document.at(pos);
    });

    if(inTable(buffer))
        tokens.push_back(new IdToken(buffer));
    else{
        if(isNumber(buffer))
            tokens.push_back(new LiteralToken(buffer));
        else
            throw std::runtime_error("Unknown variable: `" + buffer + "`, at: " + std::to_string(pos));
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
    refCount++;
    std::ifstream fs;
    fs.open(path);
    this->document = std::string((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

    LOG.createHeading("Original Input being Lexically Analysed:");
    LOG() << this->document << std::endl;

    preProcessDocument();
    start(0);
}

ACC::LexicalAnalysis::LexicalAnalysis(const ACC::LexicalAnalysis &other)
        : tokens(other.tokens), document(other.document), refCount(other.refCount),
        processed(other.processed)
{
    refCount++;
}



ACC::LexicalAnalysis::~LexicalAnalysis() {
    refCount--;
    if(refCount != 0)
        return;

    for(const auto& it : tokens)
        delete it;
}

void ACC::LexicalAnalysis::preProcessDocument() {
    document += "\nexit 0;";
}

void ACC::LexicalAnalysis::printToken() {
    LOG.createHeading("Tokens generated by the Lexical Analysis:");
    for(auto const& token : tokens){
        LOG() << token->getIdentifier() << std::endl;
    }
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

bool ACC::LexicalAnalysis::inTable(std::string idf) {
    return table.find(idf) != table.end();
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



