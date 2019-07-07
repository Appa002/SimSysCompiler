//
// Created by a_mod on 16.04.2019.
//

#include "DataStructureMovement.h"
#include <General/utils.h>

offset_t abs(offset_t num){
    return num < 0 ? (num * -1) : num; //TODO: Do properly.
}

std::string ACC::Movs::imm2bp(GeneralDataStore immediat, offset_t bpOffset) {
    GeneralDataStore immediatForAssembly;
    dWordAlignT<GeneralDataStore, uint8_t>(immediat, [&](std::vector<uint8_t> packet){
        for(auto itr = packet.rbegin(); itr != packet.rend(); ++itr){
            immediatForAssembly.push(*itr);
        }
    });

    auto sign = std::string(bpOffset >= 0 ? ("+") : ("-"));
    bpOffset = abs(bpOffset);

    std::string operatorSize;

    if(immediatForAssembly.size() == 1){
        operatorSize = "byte";
    }
    else if(immediatForAssembly.size() == 2){
        operatorSize = "word";
    }
    else if(immediatForAssembly.size() >= 3){
        operatorSize = "dword";
    }


    std::string str = "mov "+operatorSize+" [rbp "+sign+" "+std::to_string(bpOffset)+"], 0x";
    size_t count = 0;
    size_t totalSize = 0;

    for (size_t i = 0; i < immediatForAssembly.size(); i++) {
        size_t offset = str.size();
        if (count == 4) {

            if(immediatForAssembly.size() - i == 1){
                operatorSize = "byte";
                totalSize += 1;
            }
            else if(immediatForAssembly.size() - i == 2){
                operatorSize = "word";
                totalSize += 2;
            }
            else if(immediatForAssembly.size() - i >= 3){
                operatorSize = "dword";
                totalSize += 4;
            }

            str += "\nmov " + operatorSize + " [rbp "+sign+" "+std::to_string(bpOffset - i)+"], 0x";
            offset = str.size();
            count = 0;
        }

        str.insert(offset, toHex(immediatForAssembly.at(i)));
        count++;
    }

    return str;
}

