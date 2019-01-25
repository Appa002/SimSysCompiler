//
// Created by a_mod on 25.01.2019.
//

#include "Production.h"

ACC::Production::Production(ACC::Symbol head) : head(head){

}

ACC::Production::Production(ACC::Symbol head, std::vector<ACC::Symbol> body) : head(head), body(std::move(body)){

}
