//
// Created by a_mod on 22.04.2019.
//

#include "GeneralDataStore.h"
#include <stdexcept>


template<>
std::string ACC::GeneralDataStore::asT<std::string>(size_t idx) const {
    if (idx >= internalStore.size())
        throw std::runtime_error("Index out of range");

    const char *vecPtr = reinterpret_cast<const char *>(&internalStore[idx]);
    return std::string(vecPtr, internalStore.size() - idx);
}

template<>
void ACC::GeneralDataStore::storeT<std::string>(std::string data) {
    internalStore.assign(data.size(), 0x00);
    auto *vecPtr = reinterpret_cast<char *>(&internalStore[0]);
    data.copy(vecPtr, data.size());
}

size_t ACC::GeneralDataStore::size() const {
    return internalStore.size();
}

uint8_t ACC::GeneralDataStore::at(size_t idx) const {
    return internalStore[idx];
}

void ACC::GeneralDataStore::push(uint8_t value) {
    internalStore.push_back(value);
}
