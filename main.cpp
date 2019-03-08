#include <fstream>
#include <iostream>
#include <Lexical/LexicalAnalysis.h>
#include <Parser/ParseTree.h>
#include <Logger/Logger.h>
#include <AbstractSyntaxTree/AbstractSyntaxTree.h>
#include <IntermediateCodeGenerator/Operator.h>
#include <IntermediateCodeGenerator/IntermediateCode.h>
#include <IntermediateCodeGenerator/Optimizaions/Optimizations.h>
#include <AssemblyGenerator/Assembly.h>

using namespace ACC;

void runToolchainLinux(std::string filePath){
    std::string nasmCommand = "nasm -f elf64 "+ filePath +".asm";
    std::string ldCommand = "ld " + filePath + ".o";


    LOG.createHeading("Running toolchain for 64 bit Linux (nasm, ld) ...");

    LOG() << Log::Colour::Magenta << "Running nasm ";
    LOG() << Log::Colour::Blue << "("+nasmCommand+")" << std::endl << "[Nasm> ";
    LOG() << Log::Colour::Cleared << " ";
    fflush(stdout);
    int exitNasm = system(nasmCommand.c_str());
    LOG() << "" << std::endl;
    LOG() << Log::Colour::Cleared << "... exited with: " + std::to_string(exitNasm) << std::endl;
    if(exitNasm != 0){
        LOG() << Log::Colour::Red << "nasm failed; giving up on the toolchain" << std::endl;
        return;
    }

    LOG() << "" << std::endl;

    LOG() << Log::Colour::Magenta << "Running ld ";
    LOG() << Log::Colour::Blue << "("+ldCommand+")" << std::endl << "[LD> ";
    LOG() << Log::Colour::Cleared << " ";
    fflush(stdout);
    int exitLd = system(ldCommand.c_str());
    LOG() << "" << std::endl;
    LOG() << Log::Colour::Cleared << "... exited with: " + std::to_string(exitLd) << std::endl;
    if(exitLd){
        LOG() << Log::Colour::Red << "ld failed; giving up on the toolchain" << std::endl;
        return;
    }

}


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
    auto ass = Assembly();
    ass.generate(i);
    ass.print();
    ass.writeToFile();

    runToolchainLinux("./a");

    LOG.del();
    return 0;
 }