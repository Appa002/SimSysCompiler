//
// Created by a_mod on 02.01.2019.
//

#include "TokenizedInput.h"
#include <errors.h>
#include <iostream>

ACC::TokenizedInput::TokenizedInput(std::ifstream* inputFile, bool immediate, std::string lexicon) {
    this->data = std::vector<Token>();
    this->inputFile = inputFile;
    buildLexicon(std::move(lexicon));
    if (immediate)
        process();
}

ACC::TokenizedInput ACC::TokenizedInput::process() {
    error = true;
    if(processed)
        throw repeated_step_error_t("The Input file has already been tokenized.");


    std::string document((std::istreambuf_iterator<char>(*inputFile)), std::istreambuf_iterator<char>());

    for(const auto& pair : token2regex){
        for(auto it = std::sregex_iterator(document.begin(), document.end(), pair.second);
        it != std::sregex_iterator(); it++){

            auto match = std::smatch(*it);
            if(data.empty()){
                data.emplace_back(pair.first, match.position(1), cleanStr(match.str(1)));
                continue;
            }
            for (auto token = data.rbegin(); token != data.rend(); ++token){
                if (token->pos < match.position(1) && !match.str(1).empty()){
                    data.insert(token.base(), Token(pair.first, match.position(1), cleanStr(match.str(1))));
                    break;
                }
            }
        }
    }

    error = false;
    processed = true;
    return *this;
}

void ACC::TokenizedInput::buildLexicon(std::string lexicon) {
    error = true;
    std::ifstream file;
    file.open(lexicon);
    if(!file.is_open())
        throw io_error_t(("Couldn't open lexicon: \""+lexicon+"\"").c_str());

    for(std::string line; std::getline(file, line);){
        if(line.back() == '\r')
            line.erase(line.length() - 1);
        std::string token, regex;
        split(line, ',', token, regex);
        this->token2regex.emplace_back(static_cast<TokenId>(std::stoi(token)), regex);
    }

    file.close();
    error = false;
}

void ACC::TokenizedInput::split(std::string str, char determinator, std::string &lhs, std::string &rhs) {
    bool dumpingIntoLhs = true;
    for (char &c : str) {
        if(c == determinator){
            dumpingIntoLhs = false;
            continue;
        }
        if(dumpingIntoLhs)
            lhs += c;
        else
            rhs += c;
    }
}

std::vector<ACC::Token>::iterator ACC::TokenizedInput::begin() {
    return data.begin();
}

std::vector<ACC::Token>::iterator ACC::TokenizedInput::end() {
    return data.end();
}

std::string ACC::TokenizedInput::cleanStr(std::string in) {
    for(auto c = in.rbegin(); c != in.rend(); ++c){
        if(*c == '\n' || *c == '\r' || *c == ' ')
            in.erase(std::next(c).base());
    }
    return in;
}

void ACC::TokenizedInput::prettyPrint(ACC::TokenizedInput& input, const int space) {
    std::stringstream ss;
    ss << "---- Pretty Print of TokenizedInput at " << std::hex << &input << " ----" << std::endl;
    unsigned long startMsgLen = ss.str().length();
    std::cout << ss.str();

    ss.str("");
    ss << std::dec;
    std::cout << "ID";
    for(int i = 0; i < space - 2 + 1; i++)
        std::cout << " ";

    std::cout << "Pos";
    for(int i = 0; i < space - 3 + 1; i++)
        std::cout << " ";

    std::cout << "Content";
    std::cout << std::endl;

    for(const auto& token : input){
        ss.str("");
        ss << (int)token.id; // ID
        std::cout << ss.str();
        for(int i = 0; i < space - ss.str().length() + 1; i++)
            std::cout << " "; // !ID

        ss.str("");
        ss << token.pos; // Pos
        std::cout << ss.str();
        for(int i = 0; i < space - ss.str().length() + 1; i++)
            std::cout << " "; //!Pos

        ss.str("");
        ss << token.content; // Content
        std::cout << ss.str();

        std::cout << std::endl;
    }

    while (startMsgLen != 1){
        std::cout << "-";
        startMsgLen--;
    }
    std::cout << std::endl << std::endl;
}
