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

Buffers:
0 - instrPointer
1 - controlBuffer
2 - sectorBuffer

27 - first free
*/

#ifndef TRITCPU_HPP
#define TRITCPU_HPP

#include "tryteMath.hpp"
#include <vector>

#define MEMSIZE 19'683
#define INSTRSIZE 19'683

// Note: trytes internally store their data as 16-bit binary integers.
// Thus, the following enumeration is valid for direct casting to trytes.
enum instr
{
    kill = 0,
    put,
    cpy,

    incr,
    decr,
    jump,

    jumpBack,
    ifControl,
    endif,

    andEq,
    andNeq,
    andLess,

    andGreater,
    orEq,
    orNeq,

    orLess,
    orGreater,
};

// Makes intr into short and casts to tryte
tryte castInstr(instr what);

class TritCpu
{
public:
    TritCpu();
    TritCpu(tryte *Sectors[27]);

    void loadProgram(vector<tryte> &Program);

    int doInstr();

    tryte mem[MEMSIZE + INSTRSIZE];
    tryte *sectors[27];

    tryte *instrPointer = mem;
    tryte *controlBuffer = mem + 1;
    tryte *sectorBuffer = mem + 2;

protected:
    void jumpIf();
};

#endif
