//
// Created by a_mod on 04.01.2019.
//


#include <gtest/gtest.h>
#include <TokenizedInput.h>
#include <fstream>
#include <DepthParsedInput.h>
using namespace ACC;

TEST(ExpressionizedInputSuit, Parsing){
    auto stream = new std::ifstream;
    stream->open("./parsingTest.txt");
    ASSERT_EQ(stream->is_open(), true) << "Couldn't open file for testing: \"parsingTest.txt\"";

    auto t = TokenizedInput(stream);
    auto e = DepthParsedInput(t);

    std::vector<Operand> truth = {
            {
                    Token(TokenId::TOKEN_VAR, 0, "var"),
                    Token(TokenId::TOKEN_UNKNOWN, 4, "a"),
                    Token(TokenId::TOKEN_ASSIGN, 6, "="),
                    Token(TokenId::TOKEN_UNKNOWN, 8, "1"),
            },
            {
                    Token(TokenId::TOKEN_VAR, 10, "var"),
                    Token(TokenId::TOKEN_UNKNOWN, 15, "b"),
                    Token(TokenId::TOKEN_ASSIGN, 17, "="),
                    Token(TokenId::TOKEN_UNKNOWN, 19, "2"),
                    Token(TokenId::TOKEN_PLUS, 21, "+"),
                    Token(TokenId::TOKEN_UNKNOWN, 23, "2"),
            },
            {
                    Token(TokenId::TOKEN_VAR, 25, "var"),
                    Token(TokenId::TOKEN_UNKNOWN, 30, "c"),
                    Token(TokenId::TOKEN_ASSIGN, 32, "="),
                    Token(TokenId::TOKEN_UNKNOWN, 34, "a"),
                    Token(TokenId::TOKEN_PLUS, 36, "+"),
                    Token(TokenId::TOKEN_OPEN_BRACKET, 38, "("),
                    Token(TokenId::TOKEN_UNKNOWN, 39, "b"),
                    Token(TokenId::TOKEN_MINUS, 41, "-"),
                    Token(TokenId::TOKEN_UNKNOWN, 43, "1"),
                    Token(TokenId::TOKEN_CLOSED_BRACKET, 44, ")"),
            },
            {
                    Token(TokenId::TOKEN_PRINT, 46, "print"),
                    Token(TokenId::TOKEN_UNKNOWN, 53, "c"),
            }

    };

    size_t exprIdx = 0;
    size_t tokenIdx = 0;

    for(const auto& expr : e){
        tokenIdx = 0;
        for(const auto& token : expr){
            EXPECT_EQ(token, truth[exprIdx][tokenIdx]) << "Token at [" << exprIdx << "][" << tokenIdx << "] was parsed incorrectly "
                << std::endl << "Parsed(Id, pos, content): " << (int)token.id << " " << token.pos << " " << token.content
                << std::endl << "Expected(Id, pos, content): " << (int)truth[exprIdx][tokenIdx].id << " " <<
                truth[exprIdx][tokenIdx].pos << " " << truth[exprIdx][tokenIdx].content;
            ++tokenIdx;
        }
        ++exprIdx;
    }

}
