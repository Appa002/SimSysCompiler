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
#include <evaluators.h>
#include <patterns.h>

// var [a-zA-Z]+
ACC::AssignmentContext::AssignmentContext()
        : legals(
        {
                {data::numberLiteral_pattern, Instruction(InstructionId::NEW_TOKEN, new evaluator(data::number_eval))},
                {data::plus_pattern, Instruction(InstructionId::NEW_TOKEN, new evaluator(data::mathOperator_eval))},
                {data::minus_pattern, Instruction(InstructionId::NEW_TOKEN, new evaluator(data::mathOperator_eval))},
                {data::openBracket_pattern, Instruction(InstructionId::NEW_TOKEN, new evaluator(data::bracket_eval))},
                {data::closedBracket_pattern, Instruction(InstructionId::NEW_TOKEN, new evaluator(data::bracket_eval))},
                {data::id_pattern, Instruction(InstructionId::NEW_TOKEN, new evaluator(data::id_eval))},
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