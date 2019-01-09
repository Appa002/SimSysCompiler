#include <utility>

//
// Created by a_mod on 02.01.2019.
//

#ifndef SIMSYSCOMPILER_ERROR_T_H
#define SIMSYSCOMPILER_ERROR_T_H

#include <stdexcept>
#include <string>

namespace ACC{
    using parse_error_t = class ParseError : public std::runtime_error {
    public:
        ParseError(const char* msg) : std::runtime_error( ("An Error Occurred while parsing a data structure: " + std::string(msg)).c_str()) {};
        ParseError(std::string msg) : std::runtime_error( ("An Error Occurred while parsing a data structure: " + msg).c_str()) {};
    };
    using repeated_step_error_t = class RepeatedStepError : public std::runtime_error {
    public:
        RepeatedStepError(const char* msg) : std::runtime_error( ("The operation has already been done on the given data structure: " + std::string(msg)).c_str()) {};
        RepeatedStepError(std::string msg) : std::runtime_error( ("The operation has already been done on the given data structure: " + msg).c_str()) {};
    };
    using io_error_t = class IoError : public std::runtime_error {
    public:
        IoError(const char* msg) : std::runtime_error( ("A file couldn't be opened: " + std::string(msg)).c_str()) {};
        IoError(std::string msg) : std::runtime_error( ("A file couldn't be opened: " + msg).c_str()) {};
    };

}

#endif //SIMSYSCOMPILER_ERROR_T_H
