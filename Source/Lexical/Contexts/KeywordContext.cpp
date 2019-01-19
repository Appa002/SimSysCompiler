//
// Created by a_mod on 06.01.2019.
//

#include "GlobalContext.h"
#include <regex>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Contexts/KeywordContext.h>
#include <errors.h>
#include <iostream>
#include <Lexical/Tokens/PrintToken.h>
#include <evaluators.h>
// var [a-zA-Z]+
ACC::KeywordContext::KeywordContext()
        : legals(
        {
                {Pattern({"[a-zA-Z_]+| +[a-zA-Z_]+"}), Instruction(InstructionId::NEW_TOKEN, new evaluator(data::print_eval))}
        }
)
{
}

ACC::KeywordContext::KeywordContext(const ACC::KeywordContext &other) :
        legals(other.legals){
    refCounter++;
}

ACC::KeywordContext::~KeywordContext() {
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

const std::vector<ACC::IContext::match> ACC::KeywordContext::getLegals() {
    return legals;
}

ACC::Pattern ACC::KeywordContext::escapeSequence() {
    return Pattern({";| +;"});
}