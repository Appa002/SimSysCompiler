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
            if(matchCount == 1)
                return true;
        }
    }
    return false;
}

ACC::Pattern::Pattern() : regexs(){

}
