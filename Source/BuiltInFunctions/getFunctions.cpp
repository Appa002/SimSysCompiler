#include "getFunctions.h"
#include "Char.h"
#include "Num.h"

ACC::Fn ACC::BuiltIns::getCharFn_num() {
    return Char::get_num();
}

ACC::Fn ACC::BuiltIns::getNumFn_char() {
    return Num::get_char();
}
