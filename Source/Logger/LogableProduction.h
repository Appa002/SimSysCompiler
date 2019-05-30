//
// Created by a_mod on 24.05.2019.
//

#pragma once

#include <Parser/Production.h>
#include <Logger/Logger.h>
#include <grammar.h>

namespace ACC {
    class LogableProduction {
    public:
        LogableProduction(ACC::Symbol h, std::vector<ACC::Symbol> prod);
        LogableProduction() = default;
        void loadProduction(Symbol h, std::vector<Symbol> prod);
        void changeProduction(Symbol h, std::vector<Symbol> prod);
        void echoProduction();
        void green();
        void red();
        void blue();

    private:
        ACC::Symbol head = Symbol::VAR;
        std::vector<ACC::Symbol> productionToLog;
        size_t idx = 0;
    };
}

