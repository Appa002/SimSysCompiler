#include <utility>
#include <iostream>
#include <sstream>
#include "Operand.h"

ACC::Operand::Operand(std::vector<Token> _data, Operand* _parent) :
data(std::move(_data)), parent(_parent){
    sub_expression_t lhs, rhs;
    bool split = false;

    if(data.size() == 1 && !data.at(0).subToken.empty())
        data = data.at(0).subToken;

    if(data.size() == 2 && data.at(0).subToken.empty()){
        if(data.at(0).id == TokenId::TOKEN_OPEN_BRACKET)
            data.erase(data.begin());
        else if (data.at(1).id == TokenId::TOKEN_CLOSED_BRACKET)
            data.erase(data.end());
    }

    for(const auto& token : data){
        if(!split && (token.id == TokenId::TOKEN_ASSIGN || token.id == TokenId::TOKEN_PLUS || token.id == TokenId::TOKEN_MINUS)){
            split = true;
            continue;
        }

        if(!split)
            lhs.push_back(token);
        else
            rhs.push_back(token);
    }
    if(split) {
        this->lhs = new Operand(lhs, this);
        this->rhs = new Operand(rhs, this);
    }
}

std::vector<ACC::Token>::iterator ACC::Operand::begin() {
    return data.begin();
}

std::vector<ACC::Token>::iterator ACC::Operand::end() {
    return data.end();
}

void ACC::Operand::prettyPrint(std::vector<std::string>* levelStreams) {
    if((int)levelStreams->size() - 1 < treeLevel())
        levelStreams->emplace_back();

    if(parent == nullptr)
        levelStreams->at((unsigned) treeLevel()) += charRepeat(combinedLength(), ' ');
    else{
        if(parent->lhs == this){
            int prevBuff = levelStreams->at(treeLevel() - 1).length() - parent->length();
            int newBuff = prevBuff - (parent->length() / 4);
            levelStreams->at((unsigned) treeLevel()) += charRepeat(newBuff, ' ');
        }else if (parent->rhs == this){
            levelStreams->at((unsigned) treeLevel()) += charRepeat(parent->length(), ' ');
        }
    }
    levelStreams->at((unsigned) treeLevel()) += simplePrint();

    if(lhs != nullptr){
        lhs->prettyPrint(levelStreams);
    }
    if(rhs != nullptr){
        rhs->prettyPrint(levelStreams);
    }
}

ACC::Operand *ACC::Operand::findDeepestLeaf() {
    if(lhs != nullptr)
        return lhs->findDeepestLeaf();
    if(parent != nullptr && parent->rhs != nullptr && parent->rhs->rhs != nullptr)
        return parent->rhs->findDeepestLeaf();
    return this;
}

int ACC::Operand::treeLevel(int amount) {
    if(parent == nullptr)
        return amount;
    return parent->treeLevel(amount + 1);
}

unsigned long ACC::Operand::size() {
    return data.size();
}

std::string ACC::Operand::simplePrint() {
    std::string out;
    for(auto token = data.begin(); token != data.end() - 1; token++){
        out += token->content + " ";
    }
    out += data.at(data.size() - 1).content;
    return out;
}

ACC::Operand::~Operand() {
    delete lhs;
    delete rhs;
}

std::string ACC::Operand::charRepeat(int amount, char c) {
    if(amount <= 0)
        return "";
    std::string out;
    while(amount != 0){
        out += c;
        amount--;
    }
    return out;
}

int ACC::Operand::combinedLength(int n) {
    if(lhs != nullptr)
        return lhs->combinedLength(n + length());
    else
        return n + length();
}

int ACC::Operand::length() {
    std::string str = simplePrint();
    return static_cast<int>(str.length());
}

ACC::Token &ACC::Operand::at(size_t idx) {
    return data.at(idx);
}
