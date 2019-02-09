//
// Created by a_mod on 19.01.2019.
//

#include "evaluators.h"
#include <errors.h>
#include <regex>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/MathOperatorToken.h>
#include <Lexical/Tokens/BracketToken.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/EOSToken.h>
#include <Lexical/Tokens/PrintToken.h>

ACC::IToken *ACC::data::id_eval(const std::string &input, const std::string::iterator &matchStart,
                                const std::string::iterator &matchEnd) {
    const std::string document(matchStart, matchEnd);

    std::regex rgx("([a-zA-Z_]+)| +([a-zA-Z_]+)");
    if (!std::regex_search(document, rgx))
        throw lexical_error_t("Interpreted \"" + document +
                              "\" as an id in an global context, yet it doesn't match patterns described.");

    std::smatch match(*std::regex_iterator(document.begin(), document.end(), rgx));
    std::string str = match.str(1).empty() ? match.str(2) : match.str(1);
    return new IdToken(str);
}

ACC::IToken *ACC::data::mathOperator_eval(const std::string &input, const std::string::iterator &matchStart,
                                          const std::string::iterator &matchEnd) {
    const std::string document(matchStart, matchEnd);

    std::regex rgx("\\+");
    if (std::regex_search(document, rgx))
        return new MathOperatorToken(MathOperators::PLUS);
    rgx = std::regex("-");
    if (std::regex_search(document, rgx))
        return new MathOperatorToken(MathOperators::MINUS);

    throw lexical_error_t("Interpreted \"" + document +
                          "\" as an mathematical operator in an assignment context, yet it doesn't match patterns described.");
}

ACC::IToken *ACC::data::bracket_eval(const std::string &, const std::string::iterator &matchStart,
                                     const std::string::iterator &matchEnd) {
    const std::string document(matchStart, matchEnd);

    std::regex rgx("\\(");
    if (std::regex_search(document, rgx))
        return new BracketToken(BracketKind::OPEN);
    rgx = std::regex("\\)");
    if (std::regex_search(document, rgx))
        return new BracketToken(BracketKind::CLOSED);

    throw lexical_error_t("Interpreted \"" + document +
                          "\" as an bracket in an assignment context, yet it doesn't match patterns described.");

}

ACC::IToken *
ACC::data::number_eval(const std::string &, const std::string::iterator &matchStart,
                       const std::string::iterator &matchEnd) {
    const std::string document(matchStart, matchEnd);
    std::regex rgx("([0-9]+)| +([0-9]+)");
    if (!std::regex_search(document, rgx))
        throw lexical_error_t("Interpreted \"" + document +
                              "\" as an literal in an assignment context, yet it doesn't match patterns described.");

    std::smatch match(*std::regex_iterator(document.begin(), document.end(), rgx));
    std::string str = match.str(1).empty() ? match.str(2) : match.str(1);
    return new LiteralToken(str);
}

ACC::IToken *
ACC::data::var_eval(const std::string &, const std::string::iterator &, const std::string::iterator &) {
    return new VarToken();
}

ACC::IToken *
ACC::data::print_eval(const std::string &, const std::string::iterator &matchStart,
                                const std::string::iterator &matchEnd) {
    const std::string document(matchStart, matchEnd);

    std::regex rgx("print +([a-zA-Z_]+)");
    if (!std::regex_search(document, rgx))
        throw lexical_error_t("Interpreted \"" + document +
                              "\" as an `print` in an keyword context, yet it doesn't match patterns described.");

    std::smatch match(*std::regex_iterator(document.begin(), document.end(), rgx));
    return new PrintToken();
}


/* Switches... */

ACC::IContext *ACC::data::assignment_switch() {
}

ACC::IToken *ACC::data::eos_eval(const std::string &, const std::string::iterator &matchStart,
                                 const std::string::iterator &matchEnd) {
    return new EOSToken();
}
