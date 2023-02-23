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

class macro_error : public runtime_error
{
public:
    macro_error(string what) : runtime_error(what) {}
};

// Simple macros which expand into .tasl code
// These are included by default in the .tera assembler
string print(Assembler &Caller, const string &Arg);
string println(Assembler &Caller, const string &Arg);

string req(Assembler &Caller, const string &Arg);

string copyVars(Assembler &Caller, const string &Arg);
string zeroOut(Assembler &Caller, const string &Arg);

#endif
