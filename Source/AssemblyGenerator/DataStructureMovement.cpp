//
// Created by a_mod on 16.04.2019.
//

#include "DataStructureMovement.h"
#include <utils.h>

std::string ACC::Movs::c2st(std::vector<Location> constants){
    std::string str = "mov dword [rsp], 0x";
    size_t count = 0;

    for (size_t i = 0; i < constants.size(); i++) {
        if (constants[i].accessMethod == AccessMethod::CONSTANT) {
            size_t offset = str.size();
            if (count == 4) {
                str += "\nmov dword [rsp + " + std::to_string(i) + "], 0x";
                offset = str.size();
                count = 0;
            }

            str.insert(offset, toHex((unsigned)constants.at((unsigned)i).constant));
            count++;
        }
    }
    return str;
}