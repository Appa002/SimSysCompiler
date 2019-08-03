//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_ITOKEN_H
#define SIMSYSCOMPILER_ITOKEN_H

#include <string>
#include <grammar.h>

namespace ACC {
    class IContext;

    class IToken {
    public:
        Symbol id;
        const size_t lineNum;

        explicit IToken(Symbol id, size_t lineNum) : lineNum(lineNum), id(id) {};
        
        virtual std::string getIdentifier() = 0;
        virtual ~IToken() = default;
    };

    struct token_string : public std::vector<IToken*>{
        token_string();
        token_string(std::vector<IToken*> other);
        std::string createStdString();
        std::vector<IToken*> operator() (const token_string& other);
    };

}

#endif //SIMSYSCOMPILER_NEWTOKEN_H
