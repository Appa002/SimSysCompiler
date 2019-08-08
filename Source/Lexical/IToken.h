//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_ITOKEN_H
#define SIMSYSCOMPILER_ITOKEN_H

#include <string>
#include <grammar.h>

namespace ACC {

    class IToken {
    public:
        Symbol id;
        const size_t lineNum;
        std::string lineContent;

        explicit IToken(Symbol id, size_t lineNum) : lineNum(lineNum), id(id) {};

        virtual std::string getIdentifier() = 0;
        [[nodiscard]] virtual std::string getIdForErrReporting() const = 0;
        virtual ~IToken() = default;
    };

}

#endif //SIMSYSCOMPILER_NEWTOKEN_H
