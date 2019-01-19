//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_KEYWORDCONTEXT_H
#define SIMSYSCOMPILER_KEYWORDCONTEXT_H

#include <Lexical/IContext.h>

namespace ACC {
    class KeywordContext : public IContext{
    private:
        const std::vector<ACC::IContext::match> legals;
        int refCounter = 1;
    public:
        KeywordContext();
        KeywordContext(const KeywordContext& other);
        ~KeywordContext();
        const std::vector<match> getLegals() override;
        Pattern escapeSequence() override;

        static IToken* print_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);
    };
}

#endif //SIMSYSCOMPILER_KEYWORDCONTEXT_H
