/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <sstream>
#include <set>

#include "tritcpu.hpp"
#include "stdMacros.hpp"
using namespace std;

typedef string trit_assembly;
typedef pair<tryte, tryte> var;

class Assembler
{
public:
    Assembler();

    trit_assembly assemble(const string &What);
    trit_assembly encode(const tryte &What);

    map<string, string (*)(Assembler &Caller, const string &Arg)> macros;

    set<string> noArgs;

    map<string, tryte> instructions;
    map<string, tryte> functions;
    map<string, var> variables;

    stack<tryte> memStack;
    stack<tryte> ifPositions;

    tryte firstOpenAddress;
};

#endif
