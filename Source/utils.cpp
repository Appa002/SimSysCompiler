#include <utils.h>

#include "utils.h"


std::string toHex(int value) {
    std::stringstream stream;
    stream << std::hex << value;
    std::string str = stream.str();
    if(str.size() == 1)
        str = "0" + str;
    return str;
}

ACC::Stack<size_t> generateStructureStack(const std::string &structure) {
    size_t pos = 0;
    auto next = [&]() {
        while (pos < structure.size() && structure[pos] == ' ')
            pos++;
        return pos < structure.size();
    };

    auto readNum = [&]() {
        std::string out;
        for (; (int) structure[pos] >= 0x30 && (int) structure[pos] <= 0x39 && pos < structure.size(); ++pos)
            out += structure[pos];
        return std::stoi(out);
    };

    ACC::Stack<size_t> stack;

    // 5 3 2 1

    while (pos < structure.size()) {
        next();
        int num = readNum();
        stack.push(static_cast<size_t>(num));
    }


    return stack;

}

size_t getStructureStackSize (ACC::Stack<size_t> s) {
    size_t val = 0;
    for (const auto &ele : s) {
        val = val + ele;
    }
    return val;
}

std::string registerToString(ACC::Register reg) {
    switch (reg){
        case ACC::Register::rax:
            return "rax";
        case ACC::Register::rbx:
            return "rbx";
        case ACC::Register::rcx:
            return "rcx";
        case ACC::Register::rdx:
            return "rdx";
        case ACC::Register::rbp:
            return "rbp";
        case ACC::Register::rsi:
            return "rsi";
        case ACC::Register::rdi:
            return "rdi";
        case ACC::Register::rsp:
            return "rsp";
        case ACC::Register::r8:
            return "r8";
        case ACC::Register::r9:
            return "r9";
        case ACC::Register::r10:
            return "r10";
        case ACC::Register::r11:
            return "r11";
        case ACC::Register::r12:
            return "r12";
        case ACC::Register::r13:
            return "r13";
        case ACC::Register::r14:
            return "r14";
        case ACC::Register::r15:
            return "r15";
        case ACC::Register::NONE:
            throw std::runtime_error("Converting register to string which is Register::NONE.");
    }
    return "";
}

std::string numberToLetterSequence(long number) {
    std::string out;
    if(number < 0){
        out += "m";
        number *= -1;
    }

    std::string str = std::to_string(number);
    for(auto c : str){
        std::string s;
        s += c;
        char newChar = static_cast<char>(std::stoi(s) + 97);
        out += newChar;
    }
    return out;
}
