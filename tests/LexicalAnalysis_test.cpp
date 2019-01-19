#include <gtest/gtest.h>
#include <fstream>
#include <Lexical/LexicalAnalysis.h>
#include <Lexical/Tokens/VarToken.h>
#include <Lexical/Tokens/IdToken.h>
#include <Lexical/Tokens/LiteralToken.h>
#include <Lexical/Tokens/MathOperatorToken.h>
#include <Lexical/Tokens/PrintToken.h>
#include <Lexical/Tokens/EOSToken.h>
#include <Lexical/Tokens/BracketToken.h>

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
            new BracketToken(BracketKind::OPEN),
            new IdToken("b"),
            new MathOperatorToken(MathOperators::MINUS),
            new BracketToken(BracketKind::OPEN),
            new LiteralToken("1"),
            new MathOperatorToken(MathOperators::PLUS),
            new LiteralToken("2"),
            new BracketToken(BracketKind::CLOSED),
            new BracketToken(BracketKind::CLOSED),
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
                EXPECT_EQ(*(BracketToken*)token, *(BracketToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
                break;
            case Symbol::MATH_OPERATOR:
                EXPECT_EQ(*(MathOperatorToken*)token, *(MathOperatorToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
                break;
            case Symbol::PRINT:
                EXPECT_EQ(*(PrintToken*)token, *(PrintToken*)truth[idx]) << "Token at [" << idx << "] was parsed incorrectly ";
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

}
