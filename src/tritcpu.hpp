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
2 - returnPointer

27 - first free

Minimum working memory (1 sector): 19'683 trytes = 1 kilotryte ~= 1400 kb
Maximum working memory (27 sectors): 531'441 trytes = 27 kilotryte ~= 40 mb

.tasl file: Ternary ASsembly Language file
.tera file: TERnAry file (following BINary's .bin, and adding an a to be cool)
*/

/*
On properly compiling/assembling functions

Naive approach (that I've been doing):
    Store function as source code, and replace any call
    to it with the compiled version of this source code.

Better approach:
    Compile function once outside of all others, and
    store the instruction address of its start. Before
    calling a function, do the following.

    .PREV_POINTER 1         // Create PREV_POINTER
    cpy RET PREV_POINTER    // Copy old returnPointer to PREV_POINTER
    cpy INSTR RET           // Copy current address to returnPointer
    incr RET 9              // Account for these commands upon return
    put INSTR FN_ADDR       // Call fn

    <in fn>
        // fn code here     // Do something useful
        cpy RET INSTR       // Return control to caller
    <end fn>

    cpy PREV_POINTER RET    // Restore previous returnPointer
    ~PREV_POINTER           // Delete temperary variable

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
    andNeq, // doesn't work
    andLess,
    andGreater,
    orEq,
    orNeq,
    orLess,
    orGreater,
    out,
    inp,
    sector,
};

// Makes intr into short and casts to tryte
tryte castInstr(instr what);

class TritCpu
{
public:
    TritCpu();
    TritCpu(tryte *Sectors[26]);

    void loadProgram(vector<tryte> &Program);
    int doInstr();

    void useStream(ostream &Stream)
    {
        outStream = &Stream;
        return;
    }

    void useStream(istream &Stream)
    {
        inStream = &Stream;
        return;
    }

protected:
    void jumpIf();

    ostream *outStream = &cout;
    istream *inStream = &cin;

    tryte mem[MEMSIZE + INSTRSIZE];
    tryte *sectors[27];

    tryte *curSector = mem;
    tryte *instrPointer = mem;
    tryte *controlBuffer = mem + 1;
    tryte *sectorBuffer = mem + 2;
};

#endif
