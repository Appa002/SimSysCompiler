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
    if(symbol == "_start")
        return "_start";
    // Format:
    // <name> ? <argsType> . .... .
    auto typeStr = [](const Type& t){
        // Format:
        // <typeID> `_P` (if ptr)
        return t.id + (t.isPtr ? ("_P") : (""));
    };
    std::string name = symbol;
    name += "?";

    for (const Type& t : argsType)
        name += typeStr(t) + ".";

    return name;
}

ACC::Fn::Fn(const std::string & sym) : symbol(sym){

}



