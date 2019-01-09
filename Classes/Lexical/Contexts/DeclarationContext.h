//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_DECLARATIONCONTEXT_H
#define SIMSYSCOMPILER_DECLARATIONCONTEXT_H

#include <Lexical/IContext.h>

namespace ACC {
    struct DeclarationContext : public IContext {
    private:
        const std::vector<ACC::IContext::match> legals;
        int refCounter;
    public:
        DeclarationContext();
        DeclarationContext(const DeclarationContext& other);
        ~DeclarationContext();
        const std::vector<match> getLegals() override;
        Pattern escapeSequence() override;

        static IToken* var_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);
        static IToken* print_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);
        static IContext* assignment_switch();
    };
}

#endif //SIMSYSCOMPILER_INSTRUCTIONCONTEXT_H
