//
// Created by a_mod on 02.07.2019.
//

#pragma once

#include <Assembly/Fn.h>

/*! Namespace That contains the functions (c++) that return language's builtin Assembly Function (`Fn` object)*/
namespace ACC::BuiltIns{
    Fn getCharFn_num();
    Fn getNumFn_char();
}