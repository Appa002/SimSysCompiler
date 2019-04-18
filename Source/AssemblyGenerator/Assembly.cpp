#include <utility>

#include <utility>
#include <utils.h>
#include <AssemblyGenerator/DataStructureMovement.h>

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
    emplaceFunction("_start"); // Underscore is amended automatically

    for (auto it : const_cast<Code &>(ir.getCode())) {
        switch (it->id) {
            case OperatorId::IPRINT:
                OpGenerators::iPrint(it, *this);
                break;
            case OperatorId::IEXIT:
                OpGenerators::exit(it, *this);
                break;
            case OperatorId::LATTR:
                OpGenerators::lattr(it, *this);
                break;
            case OperatorId::PRINT:
                OpGenerators::print(it, *this);
                break;
            case OperatorId::IRETURN:
                OpGenerators::ireturn(it, *this);
                break;
            case OperatorId::RETURN:
                OpGenerators::ret(it, *this);
                break;
            case OperatorId::ISATTR:
                OpGenerators::isattr(it, *this);
                break;
            case OperatorId::ICALL:
                OpGenerators::icall(it, *this);
                break;
            case OperatorId::FUNCTION:
                OpGenerators::function(it, *this);
                break;
            case OperatorId::ADD:
                OpGenerators::add(it, *this);
                break;
            case OperatorId::ICOPY:
                OpGenerators::icopy(it, *this);
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

    throw std::runtime_error("Can't find function with symbol: \"" + sym + "\"");
}

ACC::AssemblyFunction &ACC::Assembly::emplaceFunction(std::string sym) {
    functionTable[sym] = AssemblyFunction(sym);
    functionStack.push(sym);
    return functionTable[sym];
}

ACC::AssemblyFunction &ACC::Assembly::fetchFunction() {
    return functionTable.at(functionStack.peek());
}

void ACC::Assembly::createStructure(ACC::Location where, std::string structure, std::vector<ACC::Location> data) {
    auto &fn = fetchFunction();
    auto structureStack = generateStructureStack(structure);
    size_t stackSize = getStructureStackSize(structureStack);

    if (where.accessMethod == AccessMethod::STACK_TOP) {
        fn.requiredStackSize += stackSize;
        for (const auto &d : data) {
            if (d.accessMethod == AccessMethod::CONSTANT){
                fn.writeLine(Movs::c2st(d));
                structureStack.pop();
            }

            if (d.accessMethod == AccessMethod::SBP_OFFSET)
                fn.writeLine(Movs::bp2st(d, structureStack));

            if(d.accessMethod == AccessMethod::REGISTER){
                fn.writeLine(Movs::r2st(d));
                structureStack.pop();
            }
        }

    } else if (where.accessMethod == AccessMethod::SBP_OFFSET) {
        if(where.offsetInfo >= 0)
            fn.requiredStackSize += stackSize;

        for (const auto &d : data) {
            if (d.accessMethod == AccessMethod::CONSTANT){
                fn.writeLine(Movs::c2bp(d, where));
                structureStack.pop();
            }

            if(d.accessMethod == AccessMethod::REGISTER){
                structureStack.pop();
                fn.writeLine(Movs::r2bp(where, d));
            }
        }
    } else if(where.accessMethod == AccessMethod::STACK_OFFSET){
        if(where.offsetInfo >= 0)
            fn.requiredStackSize += stackSize;
        for (const auto& d : data){
            if (d.accessMethod == AccessMethod::CONSTANT){
                fn.writeLine(Movs::c2so(d, where));
                structureStack.pop();
            }
        }
    } else if(where.accessMethod == AccessMethod::REGISTER){
        for (const auto& d : data){
            if(d.accessMethod == AccessMethod::SBP_OFFSET){
                fn.writeLine(Movs::bp2r(d, where));
                structureStack.pop();
            }
        }
    }
}
