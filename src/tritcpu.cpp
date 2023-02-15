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
    tryte out = tryte((short)what);
    return out;
}

TritCpu::TritCpu()
{
    *instrPointer = MEMSIZE;

    sectors[0] = mem;
    for (int i = 1; i < 27; i++)
    {
        sectors[i] = nullptr;
    }
    return;
}

TritCpu::TritCpu(tryte *Sectors[26])
{
    *instrPointer = MEMSIZE;

    sectors[0] = mem;
    for (int i = 1; i < 27; i++)
    {
        sectors[i] = Sectors[i - 1];
    }
    return;
}

void TritCpu::loadProgram(vector<tryte> &Program)
{
    for (int i = 0; i < Program.size(); i++)
    {
        mem[(int)(*instrPointer) + i] = Program[i];
    }
    return;
}

int TritCpu::doInstr()
{
    tryte *instr, *addr, *lit;

    instr = mem + *instrPointer;
    addr = mem + *instrPointer + 1;
    lit = mem + *instrPointer + 2;

    int temp;
    switch (*instr)
    {
    case kill:
        return -1;
        break;
    case put:
        curSector[*addr] = *lit;
        break;
    case cpy:
        curSector[*lit] = curSector[*addr];
        break;
    case incr:
        curSector[*addr] += *lit;
        break;
    case decr:
        curSector[*addr] -= *lit;
        break;
    case jump:
        if (*addr != tryte(0))
        {
            *instrPointer = *addr;
        }
        else
        {
            *instrPointer += (*lit - tryte(1)) * tryte(3);
        }
        break;
    case jumpBack:
        if (*addr != tryte(0))
        {
            *instrPointer = *addr;
        }
        else
        {
            *instrPointer -= (*lit + tryte(1)) * tryte(3);
        }
        break;
    case ifControl:
        if (*controlBuffer == tryte(0))
        {
            jumpIf();
        }
        break;
    case endif:
        break;
    case andEq:
        if (*controlBuffer != tryte(0))
        {
            if (curSector[*addr] == *lit)
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
            if (curSector[*addr] == *lit)
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
            if (curSector[*addr] < *lit)
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
            if (curSector[*addr] > *lit)
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
            if (curSector[*addr] == *lit)
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
            if (curSector[*addr] == *lit)
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
            if (curSector[*addr] < *lit)
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
            if (curSector[*addr] > *lit)
            {
                *controlBuffer = tryte(19'682);
            }
            else
            {
                *controlBuffer = tryte(0);
            }
        }
        break;
    case out:
        for (tryte i = 0; i < *lit; i++)
        {
            switch (curSector[*addr + i][8])
            {
            case zero: // positive int
                cout << (int)curSector[*addr] << '\n';
                break;
            case one: // negative int
                cout << '-' << (int)curSector[*addr] << '\n';
                break;
            case two: // char
                cout << (char)((int)curSector[*addr]);
                break;
            }
        }

        break;
    case inp:
        for (tryte i = 0; i < *lit; i++)
        {
            cin >> temp;
            curSector[*addr + i] = temp;
        }

        break;
    case sector:
        if (*addr != tryte(0))
        {
            curSector = sectors[*addr % tryte(27)];
        }
        else
        {
            curSector = mem;
        }
        break;

    default:
        cout << "Error during processing of instruction " << *instr << '\n';
        throw runtime_error("Could not process invalid command");
        break;
    }

    *instrPointer += tryte(3);

    return 0;
}

void TritCpu::jumpIf()
{
    tryte numIfs(1);

    while (numIfs != tryte(0))
    {
        *instrPointer += tryte(3);

        if (mem[*instrPointer] == castInstr(ifControl))
        {
            numIfs++;
        }
        else if (mem[*instrPointer] == castInstr(endif))
        {
            numIfs--;
        }
    }

    return;
}
