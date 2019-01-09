//
// Created by a_mod on 09.01.2019.
//

#ifndef SIMSYSCOMPILER_ASSIGMENTCONTEXT_H
#define SIMSYSCOMPILER_ASSIGMENTCONTEXT_H

#include <Lexical/IContext.h>

namespace ACC {
    class AssignmentContext : public IContext {
    private:
        const std::vector<ACC::IContext::match> legals;
        int refCounter;
    public:
        AssignmentContext();
        AssignmentContext(const AssignmentContext& other);
        ~AssignmentContext();
        const std::vector<match> getLegals() override;
        Pattern escapeSequence() override;

        static IToken* id_eval(const std::string &, const std::string::iterator &, const std::string::iterator &);
        static IToken* mathOperator_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);
        static IToken* bracket_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);
        static IToken* number_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);
    };
}

#endif //SIMSYSCOMPILER_ASSIGMENTCONTEXT_H
