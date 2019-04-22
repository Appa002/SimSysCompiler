//
// Created by a_mod on 22.04.2019.
//

#pragma once

#include <vector>
#include <string>
#include <stdexcept>

namespace ACC {
    class GeneralDataStore {
    private:
        std::vector<uint8_t> internalStore;

    public:
        GeneralDataStore() = default;

        uint8_t at(size_t idx);
        size_t size();

        template<class T>
        T asT(size_t idx) {
            if (idx >= internalStore.size())
                throw std::runtime_error("Index out of range");

            auto *vecPtr = reinterpret_cast<T *>(&internalStore[idx]);
            return *vecPtr;
        }

        template<class T>
        void storeT(T data) {
            internalStore.assign(sizeof(T), 0x00);
            auto *vecPtr = reinterpret_cast<T *>(&internalStore[0]);
            *vecPtr = data;
        }


    };
}

