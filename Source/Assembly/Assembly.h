//
// Created by a_mod on 10.02.2019.
//

#ifndef SIMSYSCOMPILER_INTERMEDIATECODE_H
#define SIMSYSCOMPILER_INTERMEDIATECODE_H

#include <Assembly/Code.h>
#include <AbstractSyntaxTree/AbstractSyntaxTree.h>

namespace ACC {
    class Assembly {
    private:
        Code code;

    public:
        explicit Assembly(const AbstractSyntaxTree& tree);
        void print();
        void optimize();
        const Code& getCode() const;
        void writeToFile(std::string path);

    };

}

#endif //SIMSYSCOMPILER_INTERMEDIATECODE_H
