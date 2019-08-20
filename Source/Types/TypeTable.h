//
// Created by a_mod on 20.08.2019.
//

#ifndef SIMSYSCOMPILER_TYPETABLE_H
#define SIMSYSCOMPILER_TYPETABLE_H

#include <General/Singleton.h>
#include <unordered_map>
#include <vector>

namespace ACC {
    class TypeTable : public Singleton<TypeTable> {
    private:
        /*! Maps type names (e.g. "num", "char") to their size.
         * Used to keep track of existing types and to aid in the creation of `Type` objects.*/
        std::unordered_map<std::string, size_t> sizeMap;

        std::unordered_map<std::string, std::vector<std::string>> conversionMap;

    public:
        TypeTable();


        bool isType(std::string const & id);
        size_t getSize (std::string const & id);
        void addType(std::string const & id, size_t size, const std::vector<std::string>& conversions);

    };
}

#endif //SIMSYSCOMPILER_TYPETABLE_H
