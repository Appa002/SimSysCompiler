//
// Created by a_mod on 12.06.2019.
//

#ifndef SIMSYSCOMPILER_LVALUESTRUCTURE_H
#define SIMSYSCOMPILER_LVALUESTRUCTURE_H

namespace ACC {
    class AsmAccessible{
    public:
        virtual std::string const & getAccess() const = 0;
    };
}

#endif //SIMSYSCOMPILER_LVALUESTRUCTURE_H
