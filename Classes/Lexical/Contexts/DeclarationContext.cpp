//
// Created by a_mod on 06.01.2019.
//

#include "DeclarationContext.h"
#include <regex>
#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Contexts/AssignmentContext.h>

// var [a-zA-Z]+
ACC::DeclarationContext::DeclarationContext()
        : legals(
        {
                {Pattern({"var [a-zA-Z]+ "}), Instruction(InstructionId::NEW_TOKEN, new evaluator(var_eval))},
             //   {Pattern({"print [a-zA-Z]+"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(print_eval))}, pprint with context switch.
                {Pattern({"="}), Instruction(InstructionId::CHANGE_CONTEXT, new context_switcher(assignment_switch))},
                {Pattern({"\r"}), Instruction(InstructionId::NOP, nullptr)},
                {Pattern({"\n"}), Instruction(InstructionId::NOP, nullptr)}
        }
)
{
    refCounter++;
}

ACC::DeclarationContext::DeclarationContext(const ACC::DeclarationContext &other) :
        legals(other.legals){
    refCounter++;
}

ACC::DeclarationContext::~DeclarationContext() {
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


const std::vector<ACC::IContext::match> ACC::DeclarationContext::getLegals() {
    return legals;
}

ACC::IToken* ACC::DeclarationContext::var_eval(const std::string & input, const std::string::iterator& matchStart, const std::string::iterator& matchEnd) {
    std::regex rgx("var ([a-zA-Z]+)");
    const std::string document(matchStart, matchEnd);
    std::smatch match(*std::regex_iterator(document.begin(), document.end(), rgx));

    auto token = new VarToken(match.str(1));
    return token;
}

ACC::Pattern ACC::DeclarationContext::escapeSequence() {
   return Pattern({"}"});
}

ACC::IContext *ACC::DeclarationContext::assignment_switch() {
    return new AssignmentContext;
}

ACC::IToken *
ACC::DeclarationContext::print_eval(const std::string &, const std::string::iterator &, const std::string::iterator &) {
    return new VarToken("");
}
