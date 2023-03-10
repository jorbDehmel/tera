/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#ifndef TRITCPU_HPP
#define TRITCPU_HPP

#undef DEBUG
#undef TIMER

#include "tryteMath.hpp"
#include <vector>
#include <chrono>
#include <map>

#ifdef TIMER
extern map<tryte, pair<double, int>> instrTimes;
#endif

#define MEMSIZE (int)19'683
#define INSTRSIZE 19'683

// Note: trytes internally store their data as 16-bit binary integers.
// Thus, the following enumeration is valid for direct casting to trytes.
enum instr
{
    kill = 0,    // 000 000'000'000 NOARG
    put,         // 001 000'000'001
    cpy,         // 002 000'000'002
    incr,        // 003 000'000'010
    decr,        // 004 000'000'011
    jump,        // 005 000'000'012
    jumpBack,    // 006 000'000'020
    ifControl,   // 007 000'000'021 NOARG
    endif,       // 008 000'000'022 NOARG
    andEqV,      // 009 000'000'100
    andNeqV,     // 00a 000'000'101
    andLessV,    // 00b 000'000'102
    andGreaterV, // 00c 000'000'110
    orEqV,       // 00d 000'000'111
    orNeqV,      // 00e 000'000'112
    orLessV,     // 00f 000'000'120
    orGreaterV,  // 00g 000'000'121
    out,         // 00h 000'000'122
    inp,         // 00i 000'000'200
    sector,      // 00j 000'000'201
    addV,        // 00k 000'000'202
    subtractV,   // 00l 000'000'210
    multV,       // 00m 000'000'211
    divV,        // 00n 000'000'212
    modV,        // 00o 000'000'220
    ifNever,     // 00p 000'000'221
};

enum buffers
{
    INSTR = 0,
    CONT = 1,
    RET = 2
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

    void printInstr(const tryte &From, const int &HowMany) const;

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
