//
// Created by a_mod on 19.01.2019.
//

#pragma once

#include <Lexical/IToken.h>

namespace ACC{
    namespace data{
        IToken* id_eval(const std::string &, const std::string::iterator &, const std::string::iterator &);
        IToken* mathOperator_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);
        IToken* bracket_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);
        IToken* number_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);
        IToken* var_eval(const std::string &, const std::string::iterator &, const std::string::iterator &);
        IToken* print_eval(const std::string&, const std::string::iterator&, const std::string::iterator&);

        /* Switches... */

        IContext* assignment_switch();
        IContext* keyword_switch();
    }
}