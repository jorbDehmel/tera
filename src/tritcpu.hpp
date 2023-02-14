/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

/*
Instruction layout:
1 tryte instr
1 tryte addr
1 tryte literal
*/

#ifndef TRITCPU_HPP
#define TRITCPU_HPP

#include "tryteMath.hpp"

#define MEMSIZE 19'683
#define INSTRSIZE 19'683

// Note: trytes internally store their data as 16-bit binary integers.
// Thus, the following enumeration is valid for direct casting to trytes.
enum instr
{
    kill = 0,

    put,
    copy,

};

// Makes intr into short and casts to tryte
tryte castInstr(instr what);

class TritCpu
{
public:
    tryte mem[MEMSIZE + INSTRSIZE];

    tryte *instrPointer = mem;
};

#endif
