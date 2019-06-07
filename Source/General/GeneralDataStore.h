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

        template <class T>
        static GeneralDataStore create(T elem){
            GeneralDataStore s;
            s.storeT<T>(elem);
            return s;
        }

        uint8_t at(size_t idx) const;
        size_t size() const;
        std::vector<uint8_t>& data();
        void push(uint8_t value);


        friend inline bool operator==(GeneralDataStore const & lhs, GeneralDataStore const & rhs){
            if(lhs.size() != rhs.size())
                return false;
            for(size_t i = 0; i < lhs.internalStore.size(); i++){
                if(lhs.at(i) != rhs.at(i))
                    return false;
            }
            return true;
        }

        long createNumber() const{
            if(internalStore.size() == sizeof(uint8_t))
                return asT<uint8_t>();
            if(internalStore.size() == sizeof(uint16_t))
                return asT<uint16_t>();
            if(internalStore.size() == sizeof(uint32_t))
                return asT<uint32_t>();
            if(internalStore.size() == sizeof(uint64_t))
                return asT<uint64_t>();
            throw std::runtime_error("Stored value larger than 8 byte!");
        }

        template<class T>
        T asT(size_t idx = 0) const {
            if (idx >= internalStore.size())
                throw std::runtime_error("Index out of range");

            const auto *vecPtr = reinterpret_cast<const T *>(&internalStore[idx]);
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

