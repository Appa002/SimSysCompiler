//
// Created by a_mod on 09.01.2019.
//

#include "AssignmentContext.h"
#include <regex>
#include <Lexical/Tokens/VarToken.h>

// var [a-zA-Z]+
ACC::AssignmentContext::AssignmentContext()
        : legals(
        {
                {Pattern({" +[0-9]+|[0-9]+"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(var_eval))},
                {Pattern({"\\+| +\\+"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(var_eval))},
                {Pattern({"-| +-"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(var_eval))},
                {Pattern({"\\(| +\\("}), Instruction(InstructionId::NEW_TOKEN, new evaluator(var_eval))},
                {Pattern({"\\)| +\\)"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(var_eval))},
                {Pattern({"[a-z]+|[A-Z]+| +[a-z]+| +[A-Z]+"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(var_eval))},
        }
)
{
    refCounter++;
}

ACC::AssignmentContext::AssignmentContext(const ACC::AssignmentContext &other) :
        legals(other.legals){
    refCounter++;
}

ACC::AssignmentContext::~AssignmentContext() {
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


const std::vector<ACC::IContext::match> ACC::AssignmentContext::getLegals() {
    return legals;
}

ACC::IToken* ACC::AssignmentContext::var_eval(const std::string & input, const std::string::iterator& matchStart, const std::string::iterator& matchEnd) {
  /*  std::regex rgx("var ([a-zA-Z]+)");
    const std::string document(matchStart, matchEnd);
    std::smatch match(*std::regex_iterator(document.begin(), document.end(), rgx));
*/
    auto token = new VarToken("hi, welcome to ");
    return token;
}

ACC::Pattern ACC::AssignmentContext::escapeSequence() {
    return Pattern({";"});
}
