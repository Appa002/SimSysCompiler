#include <fstream>
#include <iostream>
#include <Lexical/LexicalAnalysis.h>
#include <Parser/ParseTree.h>
#include <Logger/Logger.h>
/*
 * Steps:
 * Load
 * Tokenize
 * Expressionize
 * */

 using namespace ACC;


int main() {
    LOG.silence(false);
    auto l = LexicalAnalysis("./test.txt");
    auto p = ParseTree(l);
    p.data()->print();
    p.data()->print();
    return 0;
 }