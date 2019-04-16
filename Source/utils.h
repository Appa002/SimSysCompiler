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

std::string toHex (int value);

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
        packet.push_back(itrAble[i]);
    }

    if(!exitOnAligned){
        std::vector<ELM> danglingPacket;
        for(size_t i = lastIdx; i < itrAble.size(); i++){
            danglingPacket.push_back(itrAble[i]);
        }
        f(danglingPacket);
    }
}

#endif