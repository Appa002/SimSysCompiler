//
// Created by a_mod on 16.04.2019.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <functional>
#include <vector>
#include <sstream>
#include <ios>
#include <General/Stack.h>

/*! Expresses the parameter \p value as an x86 worthy hex value
 * (The return value doesn't contain the `0x` or `h` suffix/prefix).
 * Every byte of the parameter \p value is expressed with to hex digits (e.g.: (int) 0 becomes (hex) 00)
 * @param value The value to convert.
 * @return String that represents the parameter \p value.*/
std::string toHex(int64_t value);

ACC::Stack<size_t> generateStructureStack(const std::string &structure);

size_t getStructureStackSize (ACC::Stack<size_t> s);

/*! Converts a number to a sequence of letters representing that number;
 * every digit get represented by a letter i.e. `0 = a; 1 = b ... 9 = j`.
 * E.g.: `123` would become `bcd`. */
std::string numberToLetterSequence(long number);




/*! Splits up an object (\p itrAble) of arbitrary type `T` at every 4th element; calls function f with a vector containing
 * the 4 elements from the last split.
 * If the dataset contains elements at the end of the dataset which wouldn't naturally fall into a packet (e.g.: the
 * `5` in `1 2 3 4 5`), then this function will call \p f for a final time with the last dangling packet.
 * @param itrAble The object, of type `T`, which contains the data to split.
 * @param f A function which gets called for every split packet, as-well-as for the last dangling packet. It must take a
 * `std::vector<` *ELM* `>` as argument; it will contain the packet.
 * @tparam T The type of the \p itrAble object. It must implement: `operator[]` and `.size()` in a meaningful manner.
 * @tparam ELM The type of one element of an object of type `T`. (e.g.: `ELM` would be `char` if `T` is `std::string`).
 * */
template <class T, class ELM>
void dWordAlignT(T itrAble, std::function<void(std::vector<ELM>)> f){
    std::vector<ELM> packet;
    size_t lastIdx = 0;
    bool exitOnAligned = false;

    for(size_t i = 0; i < itrAble.size(); i++){
        if(i % 4 == 0 && i != 0){
            exitOnAligned = true;
            f(packet);
            packet.clear();
            lastIdx = i;
            if(itrAble.size() >= i)
                exitOnAligned = false;
        }
        packet.push_back(itrAble.at(i));
    }

    if(!exitOnAligned){
        std::vector<ELM> danglingPacket;
        for(size_t i = lastIdx; i < itrAble.size(); i++){
            danglingPacket.push_back(itrAble.at(i));
        }
        f(danglingPacket);
    }
}

#endif