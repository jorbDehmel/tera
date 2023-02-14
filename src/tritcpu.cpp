/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "tritcpu.hpp"

tryte castInstr(instr what)
{
}

TritCpu::TritCpu()
{
    for (int i = 0; i < 27; i++)
    {
        sectors[i] = nullptr;
    }
    return;
}

TritCpu::TritCpu(tryte *Sectors[27])
{
    for (int i = 0; i < 27; i++)
    {
        sectors[i] = Sectors[i];
    }
    return;
}

int TritCpu::doInstr()
{
    tryte *instr, *addr, *lit;
    instr = mem + *instrPointer;
    addr = mem + *instrPointer + 1;
    lit = mem + *instrPointer + 2;

    switch (*instr)
    {
    case kill:
        return -1;
        break;
    case put:
        mem[*addr] = *lit;
        break;
    case cpy:
        mem[*lit] = mem[*addr];
        break;
    case incr:
        mem[*addr] += *lit;
        break;
    case decr:
        mem[*addr] -= *lit;
        break;
    case jump:
        if (*addr != tryte(0))
        {
            *instrPointer = *addr;
        }
        else
        {
            *instrPointer += *lit;
        }
        break;
    case jumpBack:
        if (*addr != tryte(0))
        {
            *instrPointer = *addr;
        }
        else
        {
            *instrPointer -= *lit;
        }
        break;
    case ifControl:
        throw runtime_error("Unimplemented");
        break;
    case endif:
        throw runtime_error("Unimplemented");
        break;
    case andEq:
        if (*controlBuffer != tryte(0))
        {
            if (mem[*addr] == *lit)
            {
                *controlBuffer = tryte(19'682);
            }
            else
            {
                *controlBuffer = tryte(0);
            }
        }
        break;
    case andNeq:
        if (*controlBuffer != tryte(0))
        {
            if (mem[*addr] == *lit)
            {
                *controlBuffer = tryte(0);
            }
            else
            {
                *controlBuffer = tryte(19'682);
            }
        }
        break;
    case andLess:
        if (*controlBuffer != tryte(0))
        {
            if (mem[*addr] < *lit)
            {
                *controlBuffer = tryte(19'682);
            }
            else
            {
                *controlBuffer = tryte(0);
            }
        }
        break;
    case andGreater:
        if (*controlBuffer != tryte(0))
        {
            if (mem[*addr] > *lit)
            {
                *controlBuffer = tryte(19'682);
            }
            else
            {
                *controlBuffer = tryte(0);
            }
        }
        break;
    case orEq:
        if (*controlBuffer == tryte(0))
        {
            if (mem[*addr] == *lit)
            {
                *controlBuffer = tryte(19'682);
            }
            else
            {
                *controlBuffer = tryte(0);
            }
        }
        break;
    case orNeq:
        if (*controlBuffer == tryte(0))
        {
            if (mem[*addr] == *lit)
            {
                *controlBuffer = tryte(0);
            }
            else
            {
                *controlBuffer = tryte(19'682);
            }
        }
        break;
    case orLess:
        if (*controlBuffer == tryte(0))
        {
            if (mem[*addr] < *lit)
            {
                *controlBuffer = tryte(19'682);
            }
            else
            {
                *controlBuffer = tryte(0);
            }
        }
        break;
    case orGreater:
        if (*controlBuffer == tryte(0))
        {
            if (mem[*addr] > *lit)
            {
                *controlBuffer = tryte(19'682);
            }
            else
            {
                *controlBuffer = tryte(0);
            }
        }
        break;
    }

    *instrPointer += tryte(3);

    return 0;
}
