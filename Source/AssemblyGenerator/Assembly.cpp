#include <utility>
#include <utils.h>

//
// Created by a_mod on 02.03.2019.
//

#include "Assembly.h"
#include <AssemblyGenerator/OperatorGenerators.h>
#include <Logger/Logger.h>
#include <fstream>

size_t ACC::Assembly::writeToText(std::string text, size_t pos) {
    textSection.insert(textSectionPos, text);
    textSectionPos += text.size();
    return textSection.size();
}

size_t ACC::Assembly::writeToText(std::string text) {
    return writeToText(std::move(text), textSectionPos);
}

size_t ACC::Assembly::writeToData(std::string text, size_t pos) {
    dataSection.insert(pos, text);
    dataSectionPos += text.size();
    return dataSection.size();
}

size_t ACC::Assembly::writeToData(std::string text) {
    return writeToData(std::move(text), dataSectionPos);
}

std::string ACC::Assembly::combinedOutput() {
    std::string out = dataSection + "\n" + textSection;
    out += "\n";
    for (auto &function : functionTable)
        out += "global " + function.first + "\n";

    for (auto &function : functionTable)
        out += function.first + ":\n" + function.second.generateCode();

    return out;
}

std::string ACC::Assembly::getTextSection() {
    return textSection;
}

std::string ACC::Assembly::getDataSection() {
    return dataSection;
}

void ACC::Assembly::generate(const ACC::IntermediateCode &ir) {
    writeToText("section .text \n");
    writeToData("section .data \n");
    emplaceFunction("_start");
    functionStack.push("_start");

    for (auto it : const_cast<Code &>(ir.getCode())) {
        switch (it->id) {
            case OperatorId::IPRINT:
                OpGenerators::iPrint(it, *this);
                break;
            case OperatorId::IEXIT:
                OpGenerators::exit(it, *this);
                break;
            case OperatorId::IADD:
                OpGenerators::exit(it, *this);
                break;
            default:
                break;
        }
    }
}

void ACC::Assembly::print() {
    LOG.createHeading("Generated Assembly:");
    LOG() << combinedOutput();
}

void ACC::Assembly::writeToFile(std::string path) {
    std::fstream file(path, std::ios::trunc | std::ios::out);
    if (!file.is_open())
        throw std::runtime_error("Couldn't open output file at path: \"" + path + "\"");

    file << combinedOutput();
    file.close();
}

ACC::Location ACC::Assembly::fetchLocation(ACC::temporary reg) {
    if (registerTable.find(reg) != registerTable.cend())
        return registerTable.at(reg);
    return Location(AccessMethod::NONE);
}

void ACC::Assembly::emplaceLocation(ACC::temporary reg, const ACC::Location &snippet) {
    registerTable[reg] = snippet;
}

ACC::AssemblyFunction &ACC::Assembly::fetchFunction(std::string sym) {
    if (functionTable.find(sym) != functionTable.cend())
        return functionTable.at(sym);

    throw std::runtime_error("Can't find function with symbole: \"" + sym + "\"");
}

ACC::AssemblyFunction &ACC::Assembly::emplaceFunction(std::string sym) {
    return functionTable[sym] = AssemblyFunction(sym);
}

ACC::AssemblyFunction &ACC::Assembly::fetchFunction() {
    return functionTable.at(functionStack.peek());
}

void ACC::Assembly::createStructure(ACC::Location where, std::string structure, std::vector<ACC::Location> data) {
    auto getStackSize = [](Stack<size_t> s) {
        size_t val = s.pop();
        for (const auto &ele : s) {
            val = val * ele;
        }
        return val;
    };

    auto &fn = fetchFunction();
    size_t stackSize = getStackSize(generateStructureStack(structure));

    if (where.accessMethod == AccessMethod::STACK_TOP) {
        fn.requiredStackSize += stackSize;

        std::string str = "mov dword [rsp], 0x";
        size_t count = 0;

        for (size_t i = 0; i < stackSize; i++) {
            if (data[i].accessMethod == AccessMethod::CONSTANT) {
                size_t offset = str.size();
                if (count == 4) {
                    str += "\nmov dword [rsp + " + std::to_string(i) + "], 0x";
                    offset = str.size();
                    count = 0;
                }

                str.insert(offset, toHex((unsigned)data.at((unsigned)i).constant[0]));
                count++;
            }
        }
        fn.writeLine(str);

    }
}


ACC::Stack<size_t> ACC::Assembly::generateStructureStack(const std::string &structure) {
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
