//
// Created by a_mod on 03.01.2019.
//

#include <DepthParsedInput.h>
#include <errors.h>
#include <iostream>
#include "DepthParsedInput.h"


ACC::DepthParsedInput::DepthParsedInput(ACC::TokenizedInput input, bool immediate) : input(std::move(input)){
    if(immediate)
        process();
}

void ACC::DepthParsedInput::process() {
    error = true;
    if(processed){
        std::stringstream ss;
        ss << std::hex << &input;
        throw repeated_step_error_t("The Tokenized Input (at: \"" +  ss.str() + "\" has already been depth parsed.");
    }

    for(auto itr = input.begin(); itr != input.end(); itr++){
        auto& token = *itr;
        if(token.id == TokenId::TOKEN_OPEN_BRACKET){
            std::string newContent;
            for(; itr->id != TokenId::TOKEN_CLOSED_BRACKET; ++itr){
                token.subToken.push_back(*itr);
                newContent += itr->content + " ";
            }
            token.subToken.push_back(*itr);
            newContent += itr->content;
            token.content = newContent;
            token.id = TokenId::TOKEN_ENCLOSING_BRACKETS;
        }
        data.push_back(token);
    }

    error = false;
    processed = true;
}

std::vector<ACC::Token>::iterator ACC::DepthParsedInput::begin() {
    return data.begin();
}

std::vector<ACC::Token>::iterator ACC::DepthParsedInput::end() {
    return data.end();
}

void ACC::DepthParsedInput::prettyPrint() {
    std::stringstream ss;
    ss << "---- Pretty Print of DepthParsedInput at " << std::hex << this << " ----" << std::endl;
    unsigned long startMsgLen = ss.str().length();
    std::cout << ss.str();

    for(const auto& token : data){
        std::cout << "Token: " << token.content << std::endl;
        std::cout << "    Sub Token: " << std::endl;
        for(const auto& subToken : token.subToken){
            std::cout << "    " << subToken.content << std::endl;
        }
    }

    while (startMsgLen != 1) {
        std::cout << "-";
        startMsgLen--;
    }
    std::cout << std::endl << std::endl;
}