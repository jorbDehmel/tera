/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#ifndef STDMACROS_HPP
#define STDMACROS_HPP

#include "assembler.hpp"
#include "tritcpu.hpp"
using namespace std;

class Assembler;

// Simple macros which expand into .tasl code
// These are included by default in the .tera assembler
string print(Assembler &Caller, const string &Arg);
string println(Assembler &Caller, const string &Arg);

string req(Assembler &Caller, const string &Arg);

#endif
