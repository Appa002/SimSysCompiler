//
// Created by a_mod on 24.05.2019.
//

#include "LogableProduction.h"

ACC::LogableProduction::LogableProduction(ACC::Symbol h, std::vector<ACC::Symbol> prod) {
    productionToLog = std::move(prod);
    head = h;
}

void ACC::LogableProduction::echoProduction() {
    LOG() <<  ACC::data::symbolToString(head) << " -> ";
    for (auto &i : productionToLog) {
        LOG() << ACC::Log::Colour::Cleared <<  "[" << ACC::data::symbolToString(i) << "] ";
    }
    LOG() << "\n";
}

void ACC::LogableProduction::green() {
    LOG() << ACC::data::symbolToString(head) << " -> ";
    for(size_t i = 0; i <= idx; i++){
        LOG() << ACC::Log::Colour::Green << "[" <<  ACC::data::symbolToString(productionToLog[i]) << "] ";
    }


    for (size_t i = idx + 1; i < productionToLog.size(); i++)
        LOG() << ACC::Log::Colour::Cleared << "[" <<  ACC::data::symbolToString(productionToLog[i]) << "] ";
    LOG() << "\n";
    idx++;
}

void ACC::LogableProduction::red() {
    LOG() << ACC::data::symbolToString(head) << " -> ";
    for(size_t i = 0; i < idx; i++){
        LOG() << ACC::Log::Colour::Green <<  "[" << ACC::data::symbolToString(productionToLog[i]) << "] ";
    }

    LOG() << ACC::Log::Colour::Red << "[" << ACC::data::symbolToString(productionToLog[idx]) << "] ";


    for(size_t i = idx + 1; i < productionToLog.size(); i++)
        LOG() << ACC::Log::Colour::Cleared << "[" << ACC::data::symbolToString(productionToLog[i]) << "] ";
    LOG() << "\n";
    idx++;
}

void ACC::LogableProduction::loadProduction(ACC::Symbol h, std::vector<ACC::Symbol> prod) {
    head = h;
    productionToLog = prod;
    idx = 0;
}

void ACC::LogableProduction::blue() {
    LOG() << ACC::data::symbolToString(head) << " -> ";
    for(size_t i = 0; i < idx; i++){
        LOG() << ACC::Log::Colour::Green <<  "[" << ACC::data::symbolToString(productionToLog[i]) << "] ";
    }

    LOG() << ACC::Log::Colour::Blue << "[" << ACC::data::symbolToString(productionToLog[idx]) << "] ";


    for(size_t i = idx + 1; i < productionToLog.size(); i++)
        LOG() << ACC::Log::Colour::Cleared << "[" << ACC::data::symbolToString(productionToLog[i]) << "] ";
    LOG() << "\n";
    idx++;
}

void ACC::LogableProduction::changeProduction(ACC::Symbol h, std::vector<ACC::Symbol> prod) {
    head = h;
    productionToLog = prod;
}
