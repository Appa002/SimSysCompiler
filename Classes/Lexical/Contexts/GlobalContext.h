//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_DECLARATIONCONTEXT_H
#define SIMSYSCOMPILER_DECLARATIONCONTEXT_H

#include <Lexical/IContext.h>

namespace ACC {
    struct GlobalContext : public IContext {
    private:
        const std::vector<ACC::IContext::match> legals;
        int refCounter = 1;
    public:
        GlobalContext();
        GlobalContext(const GlobalContext& other);
        ~GlobalContext();
        const std::vector<match> getLegals() override;
        Pattern escapeSequence() override;

        static IToken* id_eval(const std::string &, const std::string::iterator &,
                               const std::string::iterator &);

        static IToken* var_eval(const std::string &, const std::string::iterator &,
                                const std::string::iterator &);

        static IContext* assignment_switch();
    };
}

#endif //SIMSYSCOMPILER_INSTRUCTIONCONTEXT_H
