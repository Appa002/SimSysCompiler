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

