#include <fstream>
#include <iostream>
#include <Lexical/LexicalAnalysis.h>
#include <Parser/ParseTree.h>
/*
 * Steps:
 * Load
 * Tokenize
 * Expressionize
 * */

 using namespace ACC;


int main() {
    auto l = LexicalAnalysis("(1 - 3) + (2 + 3)");
    auto p = ParseTree(l);
    return 0;
 }