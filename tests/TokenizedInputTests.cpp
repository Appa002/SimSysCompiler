//
// Created by a_mod on 04.01.2019.
//

#include <gtest/gtest.h>
#include <TokenizedInput.h>
#include <fstream>

using namespace ACC;

TEST(TokenizedInputSuit, Parsing){
    auto stream = new std::ifstream;
    stream->open("./parsingTest.txt");
    ASSERT_EQ(stream->is_open(), true) << "Couldn't open file for testing: \"parsingTest.txt\"";

    auto t = TokenizedInput(stream);
    std::vector<Token> truth;
    truth.emplace_back((TokenId)0, 0, "var");
    truth.emplace_back((TokenId)9, 4, "a");
    truth.emplace_back((TokenId)1, 6, "=");
    truth.emplace_back((TokenId)9, 8, "1");
    truth.emplace_back((TokenId)2, 9, ";");
    truth.emplace_back((TokenId)8, 10, "");
    truth.emplace_back((TokenId)0, 10, "var");
    truth.emplace_back((TokenId)9, 15, "b");
    truth.emplace_back((TokenId)1, 17, "=");
    truth.emplace_back((TokenId)9, 19, "2");
    truth.emplace_back((TokenId)3, 21, "+");
    truth.emplace_back((TokenId)9, 23, "2");
    truth.emplace_back((TokenId)2, 24, ";");
    truth.emplace_back((TokenId)8, 25, "");
    truth.emplace_back((TokenId)0, 25, "var");
    truth.emplace_back((TokenId)9, 30, "c");
    truth.emplace_back((TokenId)1, 32, "=");
    truth.emplace_back((TokenId)9, 34, "a");
    truth.emplace_back((TokenId)3, 36, "+");
    truth.emplace_back((TokenId)6, 38, "(");
    truth.emplace_back((TokenId)9, 39, "b");
    truth.emplace_back((TokenId)4, 41, "-");
    truth.emplace_back((TokenId)9, 43, "1");
    truth.emplace_back((TokenId)7, 44, ")");
    truth.emplace_back((TokenId)2, 45, ";");
    truth.emplace_back((TokenId)8, 46, "");
    truth.emplace_back((TokenId)5, 46, "print");
    truth.emplace_back((TokenId)9, 53, "c");
    truth.emplace_back((TokenId)2, 54, ";");

    size_t idx = 0;
    for (const auto& token : t){
        EXPECT_EQ(token, truth[idx]) << "The token " << idx  << " wasn't parsed correctly!";
        ++idx;
    }

    delete stream;
}
