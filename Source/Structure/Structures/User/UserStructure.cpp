//
// Created by a_mod on 31.08.2019.
//

#include "UserStructure.h"
#include <Error/Errors.h>
#include <Assembly/Code.h>

ACC::UserStructure::UserStructure(ACC::ValueCategory v, const ACC::Type& t) : ComplexStructure(v, t), type(t), valueCategory(v){

}

std::shared_ptr<ACC::Structure> ACC::UserStructure::operatorCopy(std::shared_ptr<Structure> obj, ACC::Code & code) {
    if(!hasCopyFunc){
        if(obj->type != this->type)
            throw errors::UnimplementedFunction(nullptr, type.id, "operatorCopy("+type.id+")");

        auto& fn = code.getFnSymbol();
        fn.writeLine("call ??generalCopy"); //Move size and address

        return obj;
    }

    std::vector<Fn> overloads;
    try {
        overloads = code.getFnOverloads("?" + type.id + ".operatorCopy");
    }
    catch (errors::MissingOverload&) {
        throw errors::UnimplementedFunction(nullptr, type.id, "operatorCopy(" + obj->type.id + ")");
    }

    auto& fn = code.getFnSymbol();

    for(auto const & overload : overloads){
        if(overload.argsType[0] == obj->type){
            fn.writeLine("call " + overloads[0].mangledName());
            return obj;
        }
    }

    throw errors::MissingOverload(nullptr, "operatorCopy(" + obj->type.id + ") for `" + type.id + "`");

}
