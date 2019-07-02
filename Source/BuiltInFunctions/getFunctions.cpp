#include "getFunctions.h"
#include "Char.h"
#include "Num.h"

ACC::Fn ACC::BuiltIns::getCharFn() {
    return Char::get();
}

ACC::Fn ACC::BuiltIns::getNumFn() {
    return Num::get();
}
