/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#ifndef STDMACROS_HPP
#define STDMACROS_HPP

#include "tritcpu.hpp"

// Simple macros which expand into .tasl code
// These are included by default in the .tera assembler
namespace stdMacros
{
    string print(const string &Arg);
    string println(const string &Arg);
};

#endif
