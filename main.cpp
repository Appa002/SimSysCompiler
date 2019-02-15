#include <fstream>
#include <iostream>
#include <Lexical/LexicalAnalysis.h>
#include <Parser/ParseTree.h>
#include <Logger/Logger.h>
#include <AbstractSyntaxTree/AbstractSyntaxTree.h>
#include <IntermediateCodeGenerator/Operator.h>
#include <IntermediateCodeGenerator/IntermediateCode.h>
#include <IntermediateCodeGenerator/Optimizaions/Optimizations.h>
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
    i.optimize();
    return 0;
 }