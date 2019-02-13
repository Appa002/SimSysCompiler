//
// Created by a_mod on 11.02.2019.
//

#ifndef SIMSYSCOMPILER_UTILS_H
#define SIMSYSCOMPILER_UTILS_H


#include <string>
#include <IntermediateCodeGenerator/RepresentationTypes.h>
#include <Logger/Logger.h>
#include <IntermediateCodeGenerator/Code.h>

namespace ACC{
    class DependencyElement;
    template <class A, class B> struct Tuple;

    std::string printAsTemporary(ACC::temporary temp);
    std::string opToString(Operator op);
    ACC::DependencyElement *createDependencyGraph(ACC::Tuple<ACC::Operator *, size_t> start, ACC::Code &input);

    template <class A, class B>
    struct Tuple{
        A a;
        B b;
    };

    struct DependencyElement{
        DependencyElement() = default;
        DependencyElement(Operator* op, size_t idx);
        ~DependencyElement();

        Operator* op = nullptr;
        DependencyElement* lhs = nullptr;
        DependencyElement* rhs = nullptr;

        size_t idx = 0;
        bool dead = false;

        void print(std::string indent, bool isLast) const;

    };

}

#endif //SIMSYSCOMPILER_UTILS_H
