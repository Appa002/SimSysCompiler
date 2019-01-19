//
// Created by a_mod on 09.01.2019.
//

#include "AssignmentContext.h"
#include <regex>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/MathOperatorToken.h>
#include <Lexical/Tokens/BracketToken.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <iostream>
#include <errors.h>

// var [a-zA-Z]+
ACC::AssignmentContext::AssignmentContext()
        : legals(
        {
                {Pattern({" +[0-9]+|[0-9]+"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(number_eval))},
                {Pattern({"\\+| +\\+"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(mathOperator_eval))},
                {Pattern({"-| +-"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(mathOperator_eval))},
                {Pattern({"\\(| +\\("}), Instruction(InstructionId::NEW_TOKEN, new evaluator(bracket_eval))},
                {Pattern({"\\)| +\\)"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(bracket_eval))},
                {Pattern({"[a-zA-Z_]+| +[a-zA-Z_]+"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(id_eval))},
        }
)
{
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

ACC::Pattern ACC::AssignmentContext::escapeSequence() {
    return Pattern({";| +;"});
}

ACC::IToken* ACC::AssignmentContext::id_eval(const std::string &input, const std::string::iterator &matchStart,
                                             const std::string::iterator &matchEnd) {
    const std::string document(matchStart, matchEnd);

    std::regex rgx("([a-zA-Z_]+)| +([a-zA-Z_]+)");
    if(!std::regex_search(document, rgx))
        throw lexical_error_t("Interpreted \""+document+"\" as an id in an global context, yet it doesn't match patterns described.");

    std::smatch match(*std::regex_iterator(document.begin(), document.end(), rgx));
    std::string str = match.str(1).empty() ? match.str(2) : match.str(1);
    return new IdToken(str);
}

ACC::IToken *ACC::AssignmentContext::mathOperator_eval(const std::string  & input, const std::string::iterator & matchStart,
                                                       const std::string::iterator & matchEnd) {
    const std::string document(matchStart, matchEnd);

    std::regex rgx("\\+");
    if(std::regex_search(document, rgx))
        return new MathOperatorToken(MathOperators::PLUS);
    rgx = std::regex("-");
    if(std::regex_search(document, rgx))
        return new MathOperatorToken(MathOperators::MINUS);

    throw lexical_error_t("Interpreted \""+document+"\" as an mathematical operator in an assignment context, yet it doesn't match patterns described.");
}

ACC::IToken *ACC::AssignmentContext::bracket_eval(const std::string &, const std::string::iterator & matchStart,
                                                  const std::string::iterator & matchEnd) {
    const std::string document(matchStart, matchEnd);

    std::regex rgx("\\(");
    if(std::regex_search(document, rgx))
        return new BracketToken(BracketKind::OPEN);
    rgx = std::regex("\\)");
    if(std::regex_search(document, rgx))
        return new BracketToken(BracketKind::CLOSED);

    throw lexical_error_t("Interpreted \""+document+"\" as an bracket in an assignment context, yet it doesn't match patterns described.");

}

ACC::IToken *
ACC::AssignmentContext::number_eval(const std::string &, const std::string::iterator & matchStart, const std::string::iterator & matchEnd) {
    const std::string document(matchStart, matchEnd);
    std::regex rgx("([0-9]+)| +([0-9]+)");
    if(!std::regex_search(document, rgx))
        throw lexical_error_t("Interpreted \""+document+"\" as an literal in an assignment context, yet it doesn't match patterns described.");

    std::smatch match(*std::regex_iterator(document.begin(), document.end(), rgx));
    std::string str = match.str(1).empty() ? match.str(2) : match.str(1);
    return new LiteralToken(str);
}
