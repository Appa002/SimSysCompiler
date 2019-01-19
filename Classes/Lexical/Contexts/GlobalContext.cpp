//
// Created by a_mod on 06.01.2019.
//

#include "GlobalContext.h"
#include <regex>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Contexts/AssignmentContext.h>
#include <Lexical/Contexts/KeywordContext.h>
#include <errors.h>
#include <Lexical/Tokens/VarToken.h>

// var [a-zA-Z]+
ACC::GlobalContext::GlobalContext()
        : legals(
        {
                {Pattern({"[a-zA-Z_]+ | +[a-zA-Z_]+ "}), Instruction(InstructionId::NEW_TOKEN, new evaluator(id_eval))},
                {Pattern({"var| +var"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(var_eval))},

                {Pattern({"print"}), Instruction(InstructionId::CHANGE_CONTEXT, new context_switcher([](){ return new KeywordContext(); }))},
                {Pattern({"="}), Instruction(InstructionId::CHANGE_CONTEXT, new context_switcher(assignment_switch))},
        }
)
{
}

ACC::GlobalContext::GlobalContext(const ACC::GlobalContext &other) :
        legals(other.legals){
    refCounter++;
}

ACC::GlobalContext::~GlobalContext() {
    refCounter--;
    if(refCounter != 0)
        return;

    for(const auto& legal : legals){
        auto instruction = legal.second;
        if(instruction.id == InstructionId::NEW_TOKEN)
            delete static_cast<Instruction::token_func*>(instruction.func);
        else if (instruction.id == InstructionId::CHANGE_CONTEXT)
            delete static_cast<Instruction::context_func*>(instruction.func);
    }
}


const std::vector<ACC::IContext::match> ACC::GlobalContext::getLegals() {
    return legals;
}

ACC::IToken* ACC::GlobalContext::id_eval(const std::string &input, const std::string::iterator &matchStart,
                                         const std::string::iterator &matchEnd) {
    const std::string document(matchStart, matchEnd);

    std::regex rgx("([a-zA-Z_]+)| +([a-zA-Z_]+)");
    if(!std::regex_search(document, rgx))
        throw lexical_error_t("Interpreted \""+document+"\" as an id in an global context, yet it doesn't match patterns described.");

    std::smatch match(*std::regex_iterator(document.begin(), document.end(), rgx));
    std::string str = match.str(1).empty() ? match.str(2) : match.str(1);
    return new IdToken(str);
}

ACC::Pattern ACC::GlobalContext::escapeSequence() {
   return Pattern({"}"});
}

ACC::IContext *ACC::GlobalContext::assignment_switch() {
    return new AssignmentContext;
}

ACC::IToken *
ACC::GlobalContext::var_eval(const std::string &, const std::string::iterator &, const std::string::iterator &) {
    return new VarToken();
}
