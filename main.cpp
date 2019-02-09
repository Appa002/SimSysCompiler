#include <fstream>
#include <iostream>
#include <Lexical/LexicalAnalysis.h>
#include <Parser/ParseTree.h>
#include <Logger/Logger.h>
#include <AbstractSyntaxTree/AbstractSyntaxTree.h>
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
    l.printToken();
    auto p = ParseTree(l);
    p.getRoot()->print();
    auto a = AbstractSyntaxTree(p);
    a.root->print();
    return 0;
 }