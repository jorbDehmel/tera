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

#include "tritcpu.hpp"
using namespace std;

typedef string trit_assembly;

class Assembler
{
public:
    Assembler();

    trit_assembly assemble(const string &What);
    trit_assembly encode(const tryte &What);

protected:
    map<string, tryte> instructions;
    map<string, tryte> functions;
    map<string, tryte> variables;
    stack<tryte> memStack;
    stack<tryte> ifPositions;

    tryte firstOpenAddress;
};

#endif
