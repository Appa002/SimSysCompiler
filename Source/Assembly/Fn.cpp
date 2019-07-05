//
// Created by a_mod on 16.05.2019.
//

#include "Fn.h"

void ACC::Fn::writeLine(std::string const &line) {
    code += line + "\n";
}

std::string ACC::Fn::generate() const {
    std::string out;
    out += "push rbp\n";
    out += "mov rbp, rsp\n";
    out += "sub rsp, " + std::to_string(curBpOffset) + "\n";
    out += code;
    return out;
}

bool ACC::Fn::matches(std::string name, ACC::Type returnType, std::vector<ACC::Type> argsType) {
    return name == symbol && returnType == this->returnType && argsType == this->argsType;
}


std::string ACC::Fn::mangledName() const {
    // Format:
    // <name> ? <argsType> _ .... _
    auto typeStr = [](Type t){
        // Format:
        // <typeID> . <pointingTO>
        return std::to_string(t.getId()) + "." + std::to_string(t.getPointingTo().getId());
    };
    std::string name = symbol;
    name += "?";

    for (Type t : argsType)
        name += typeStr(t);

    return name;
}

ACC::Fn::Fn(const std::string & sym) : symbol(sym){

}



