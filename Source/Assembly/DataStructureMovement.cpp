//
// Created by a_mod on 16.04.2019.
//

#include "DataStructureMovement.h"
#include <utils.h>

offset_t abs(offset_t num){
    return num < 0 ? (num * -1) : num; //TODO: Do properly.
}

std::string ACC::Movs::imm2st(const GeneralDataStore &immediat){
    std::string str = "mov dword [rsp], 0x";
    size_t count = 0;

    for (size_t i = 0; i < immediat.size(); i++) {
            size_t offset = str.size();
            if (count == 4) {
                str += "\nmov dword [rsp + " + std::to_string(i) + "], 0x";
                offset = str.size();
                count = 0;
            }

            str.insert(offset, toHex(immediat.at(i)));
            count++;
    }
    return str;
}

std::string ACC::Movs::bp2st(offset_t offset, size_t count) {
    auto sign = std::string(offset >= 0 ? ("+") : ("-"));
    offset = abs(offset);
    std::string out;

    // TODO: Don't do this byte by byte.

    for(size_t i = 0; i < count; i++){
        out += "\nmov byte al, [rbp"+sign+std::to_string(offset)+"]";
        out += "\nmov byte [rsp + "+std::to_string(i)+"], al";
        offset += 1;
    }
    return out;
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
    size_t totalSize = 0;

    if(immediatForAssembly.size() == 1){
        operatorSize = "byte";
    }
    else if(immediatForAssembly.size() == 2){
        operatorSize = "word";
        totalSize = 2;
    }
    else if(immediatForAssembly.size() >= 3){
        totalSize = 4;
        operatorSize = "dword";
    }

    std::string str = "mov "+operatorSize+" [rbp "+sign+" "+std::to_string(bpOffset)+"], 0x";
    size_t count = 0;

    for (size_t i = 0; i < immediatForAssembly.size(); i++) {
        size_t offset = str.size();
        if (count == 4) {

            size_t chunckSize = 0;
            if(immediatForAssembly.size() - i == 1){
                operatorSize = "byte";
                chunckSize = 1;
            }
            else if(immediatForAssembly.size() - i == 2){
                operatorSize = "word";
                chunckSize = 2;
            }
            else if(immediatForAssembly.size() - i >= 3){
                operatorSize = "dword";
                chunckSize = 4;
            }

            totalSize += chunckSize;
            str += "\nmov " + operatorSize + " [rbp "+sign+" "+std::to_string(bpOffset - i)+"], 0x";
            offset = str.size();
            count = 0;
        }

        str.insert(offset, toHex(immediatForAssembly.at(i)));
        count++;
    }

    return str;
}

std::string ACC::Movs::r2bp(offset_t offset, std::string reg) {
    auto sign = std::string(offset >= 0 ? ("+") : ("-"));
    offset = abs(offset);
    return "mov [rbp"+ sign + std::to_string(offset) + "], " + reg;
}

std::string ACC::Movs::imm2so(GeneralDataStore immediat, offset_t offset) {
    auto sign = std::string(offset >= 0 ? ("+") : ("-"));
    offset = abs(offset);

    std::string operatorSize;
    size_t totalSize = 0;

    if(immediat.size() == 1){
        operatorSize = "byte";
    }
    else if(immediat.size() == 2){
        operatorSize = "word";
        totalSize = 2;
    }
    else if(immediat.size() >= 4){
        totalSize = 4;
        operatorSize = "dword";
    }

    std::string str = "mov "+operatorSize+" [rsp "+sign+" "+std::to_string(offset + totalSize)+"], 0x";
    size_t count = 0;

    for (size_t i = 0; i < immediat.size(); i++) {
        size_t offset = str.size();
        if (count == 4) {

            size_t chunckSize = 0;
            if(immediat.size() - i == 1){
                operatorSize = "byte";
                chunckSize = 1;
            }
            else if(immediat.size() - i == 2){
                operatorSize = "word";
                chunckSize = 2;
            }
            else if(immediat.size() - i >= 4){
                operatorSize = "dword";
                chunckSize = 4;
            }

            totalSize += chunckSize;
            str += "\nmov " + operatorSize + " [rsp "+sign+" "+std::to_string(offset + totalSize)+"], 0x";
            offset = str.size();
            count = 0;
        }

        str.insert(offset, toHex(immediat.at(i)));
        count++;
    }

    return str;
}

std::string ACC::Movs::r2st(std::string reg) {
    return "mov [rsp], " + reg;
}

std::string ACC::Movs::bp2r(offset_t offset, std::string reg) {
    auto sign = std::string(offset >= 0 ? ("+") : ("-"));
    offset = abs(offset);

    return "mov " + reg +", [rbp" + sign + std::to_string(offset) + "]";
}

