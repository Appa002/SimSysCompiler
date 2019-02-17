//
// Created by a_mod on 10.02.2019.
//

#ifndef SIMSYSCOMPILER_CODE_H
#define SIMSYSCOMPILER_CODE_H

#include <vector>
#include <string>
#include <IntermediateCodeGenerator/Operator.h>
#include <unordered_map>

namespace ACC{

    struct Dependency{
        temporary temp = 0;
        Operator* op = nullptr;
    };

    class Code {
    private:
        std::vector<Operator*> data;
        std::vector<Operator*> deadOperators;
        std::unordered_map<std::string, Dependency> symTable;
        temporary temporaryCounter = 1;
        int ref = 1;


    public:
        Code();
        ~Code();
        Code(Code const & other);
        Dependency& getSymbol(std::string sym);
        Dependency& emplaceSymbol(std::string sym, Operator* op);
        void pushOp(Operator *const &op);

        /** This function removes an Operator from the generated code such that the dependency graph of the operators
         * stays intact. This only works for unary operators (i.e. the operator only uses the fields `result` and `lhs`).
         * For instance, `Copy` is such an operator, it only takes the register to copy and the register to copy it to and therefore
         * is a unary operator.
         * */
        void removeUnary(size_t idx);

        void remove(size_t idx);

        void deleteDead();

        void makeOperatorDead(size_t idx);

        Dependency createTemporary();
        Operator* at(size_t idx);

        std::vector<Operator*>::iterator begin();
        std::vector<Operator*>::iterator end();

        std::vector<Operator*>& getData();
        void print();

    };
}

#endif //SIMSYSCOMPILER_CODE_H
