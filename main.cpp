#include <fstream>
#include <iostream>
#include <Lexical/LexicalAnalysis.h>
#include <Parser/ParseTree.h>
#include <Logger/Logger.h>
#include <AbstractSyntaxTree/AbstractSyntaxTree.h>
#include <IntermediateCodeGenerator/RepresentationTypes.h>
#include <IntermediateCodeGenerator/IntermediateCode.h>
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
    a.print();
    auto i = IntermediateCode(a);
    i.print();
    return 0;
 }