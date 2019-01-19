//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_PATTERN_H
#define SIMSYSCOMPILER_PATTERN_H

#include <regex>

namespace ACC {
    class Pattern {
    private:
        std::vector<std::regex> regexs;
    public:
        explicit Pattern(std::vector<std::string> str);
        explicit Pattern();
        bool matches(const std::string::iterator& itr, size_t range);
    };
}

#endif //SIMSYSCOMPILER_PATTERN_H
