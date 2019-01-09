//
// Created by a_mod on 06.01.2019.
//

#ifndef SIMSYSCOMPILER_GENERATOR_H
#define SIMSYSCOMPILER_GENERATOR_H

#include "DepthParsedInput.h"
#include "OperandHandler.h"

namespace ACC {
    struct Variable{
        std::string idf = "";
        std::string code = "";
    };

    struct Command{
        std::string idf = "";
        std::string code = "";
    };

    struct LineOfCode{
        std::string code = "";
        LineOfCode(std::string s) : code(std::move(s)) {}
    };

    class Generator {
    private:
        OperandHandler input;

        void handleVariable(Operand *operand);
        void handleKeyWord(Operand *operand);
        void delegate(Operand* operand);

        bool isVariableDefined(std::string idf);
        bool isNumber(std::string idf);

        std::string eval(Operand* op, std::string code = "");
        std::string getVariable(std::string idf);
        std::string evalLiteral(std::string idf);

    public:
        explicit Generator(OperandHandler input);

        std::vector<Variable> variables;
        std::vector<Command> commands;
        std::vector<LineOfCode> result;
    };
}

#endif //SIMSYSCOMPILER_PARSER_H
