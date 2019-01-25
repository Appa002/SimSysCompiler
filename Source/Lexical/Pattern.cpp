#include <utility>
#include "Pattern.h"
#include <regex>
#include <string>
#include <iostream>

ACC::Pattern::Pattern(std::vector<std::string> strings){
    for(auto& string : strings){
        regexs.emplace_back(string);
    }
}

bool ACC::Pattern::matches(const std::string::iterator &itr, size_t range) {
    const std::string document(itr, itr+range);
    for(const auto& rgx : regexs) {
        if (std::regex_match(document, rgx)){
            std::ptrdiff_t const matchCount(std::distance(
                    std::sregex_iterator(document.begin(), document.end(), rgx),
                    std::sregex_iterator()));
            bool good = true;

            if(!bad.empty()){
                for(const auto& badR : bad){
                    if(std::regex_search(document, badR)){
                        good = false;
                        break;
                    }
                }
            }

            if(matchCount == 1 && good)
                return true;
        }
    }
    return false;
}

ACC::Pattern::Pattern() : regexs(){

}

ACC::Pattern::Pattern(std::vector<std::string> str, std::vector<std::string> bad) {
    for(auto& string : str){
        regexs.emplace_back(string);
    }

    for(auto& string : bad){
        this->bad.emplace_back(string);
    }
}
