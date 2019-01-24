#include <utility>

//
// Created by a_mod on 06.01.2019.
//

#include "IToken.h"

std::string ACC::token_string::createStdString() {
    std::string out;
    for(auto const& token : *this){
        out += token->getIdentifier() + " | ";
    }
    return out;
}

std::vector<ACC::IToken *> ACC::token_string::operator()(const ACC::token_string &other) {
    return *this;
}

ACC::token_string::token_string(std::vector<ACC::IToken *> other) : std::vector<IToken*>(std::move(other)){

}

ACC::token_string::token_string() : std::vector<IToken*>(){

}
