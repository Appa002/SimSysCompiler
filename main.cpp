#include <fstream>
#include <TokenizedInput.h>
#include <iostream>
#include <DepthParsedInput.h>
#include <OperandHandler.h>
#include <Generator.h>
#include <Lexical/LexicalAnalysis.h>
/*
 * Steps:
 * Load
 * Tokenize
 * Expressionize
 * */

 using namespace ACC;


int main() {
    auto l = LexicalAnalysis("./test.txt");
    return 0;
 }