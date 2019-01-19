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
    auto l = LexicalAnalysis("./test.txt");
    auto p = ParseTree(l);
    return 0;
 }