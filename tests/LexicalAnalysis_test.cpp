#include <gtest/gtest.h>
#include <fstream>
#include <Lexical/LexicalAnalysis.h>
#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <Lexical/Tokens/MathOperatorToken.h>
#include <Lexical/Tokens/SyscallToken.h>
#include <Lexical/Tokens/EOSToken.h>
#include <Lexical/Tokens/ClosedBracketToken.h>
#include "Production.h"

using namespace ACC;

TEST(ExpressionizedInputSuit, Parsing) {
    auto t = LexicalAnalysis("./parsingTest.txt");
    std::vector<IToken *> truth = {
            new VarToken(),
            new IdToken("a"),
            new LiteralToken("1"),
            new EOSToken(),

            new VarToken(),
            new IdToken("b"),
            new LiteralToken("2"),
            new MathOperatorToken(MathOperators::PLUS),
            new LiteralToken("2"),
            new EOSToken(),

            new VarToken(),
            new IdToken("c"),
            new IdToken("a"),
            new MathOperatorToken(MathOperators::PLUS),
            new ClosedBracketToken(BracketKind::OPEN),
            new IdToken("b"),
            new MathOperatorToken(MathOperators::MINUS),
            new ClosedBracketToken(BracketKind::OPEN),
            new LiteralToken("1"),
            new MathOperatorToken(MathOperators::PLUS),
            new LiteralToken("2"),
            new ClosedBracketToken(BracketKind::CLOSED),
            new ClosedBracketToken(BracketKind::CLOSED),
            new EOSToken(),

            new PrintToken("c"),
            new EOSToken()

    };

    size_t idx = 0;

    for (const auto &token : t) {
        switch (token->id){
            case Symbol::VAR:
                EXPECT_EQ(*(VarToken*)token, *(VarToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
                break;
            case Symbol::ID:
                EXPECT_EQ(*(IdToken*)token, *(IdToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
                break;
            case Symbol::BRACKET:
                EXPECT_EQ(*(ClosedBracketToken*)token, *(ClosedBracketToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
                break;
            case Symbol::MATH_OPERATOR:
                EXPECT_EQ(*(MathOperatorToken*)token, *(MathOperatorToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
                break;
            case Symbol::SYSCALL:
                EXPECT_EQ(*(SyscallToken*)token, *(SyscallToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
                break;
            case Symbol::LITERAL:
                EXPECT_EQ(*(LiteralToken*)token, *(LiteralToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
                break;
            case Symbol::EOS:
                EXPECT_EQ(*(EOSToken*)token, *(EOSToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
                break;
            case Symbol::none_terminals_start:
                throw std::runtime_error("Token was read as an none_terminals_start token, which should never happen");
            case Symbol::expr:
                throw std::runtime_error("Token after Lexical analysis was read as an noneterminal.");
            case Symbol::stmt:
                throw std::runtime_error("Token after Lexical analysis was read as an noneterminal.");
        }
        ++idx;
    }

    for(auto const& token : truth)
        delete token;

}
