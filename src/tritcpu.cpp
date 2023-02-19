/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "tritcpu.hpp"

#undef DEBUG

tryte castInstr(instr what)
{
    tryte out = tryte((short)what);
    return out;
}

TritCpu::TritCpu()
{
    *instrPointer = 2 * MEMSIZE / 3;

    sectors[0] = mem;
    for (int i = 1; i < 27; i++)
    {
        sectors[i] = nullptr;
    }
    return;
}

TritCpu::TritCpu(tryte *Sectors[26])
{
    *instrPointer = 2 * MEMSIZE / 3;

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

void TritCpu::printInstr(const tryte &From, const int &HowMany) const
{
    for (int i = 0; i < HowMany; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            cout << '\n';
        }
        cout << mem[From + tryte(i)] << '\t';
    }
    cout << '\n';

    return;
}

int TritCpu::doInstr()
{
    if (*instrPointer % tryte(3) != tryte(0))
    {
        throw runtime_error("Illegal instruction postition");
    }

    tryte *instruc, *addr, *lit;

    instruc = mem + *instrPointer;
    addr = mem + *instrPointer + 1;
    lit = mem + *instrPointer + 2;

#ifdef DEBUG
    cout << "Pos:   " << *instrPointer << '\n'
         << "Instr: " << *instruc << '\n'
         << "Addr:  " << *addr << '\n'
         << "Lit:   " << *lit << "\n"
         << "Ret:   " << mem[2] << "\n\n";
#endif

    int temp;
    switch (*instruc)
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
        if (*lit != tryte(0))
        {
            *instrPointer += (*lit - tryte(1)) * tryte(3);
        }
        else
        {
            *instrPointer = *addr - tryte(3);
        }
        break;
    case jumpBack:
        if (*lit != tryte(0))
        {
            *instrPointer -= (*lit + tryte(1)) * tryte(3);
        }
        else
        {
            *instrPointer = *addr - tryte(3);
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
        cout << "Entered andNeq\n";
        if (*controlBuffer != tryte(0))
        {
            cout << "andNeq replacing contents of control buffer\n";
            if (curSector[*addr] != *lit)
            {
                *controlBuffer = tryte(19'682);
            }
            else
            {
                *controlBuffer = tryte(0);
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
            if (curSector[*addr] != *lit)
            {
                *controlBuffer = tryte(19'682);
            }
            else
            {
                *controlBuffer = tryte(0);
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
        for (int i = 0; i < *lit; i++)
        {
            switch ((curSector[*addr + tryte(i)])[8])
            {
            case zero: // positive int
                cout << (int)curSector[*addr + tryte(i)] << '\n';
                break;
            case one: // negative int
                cout << '-' << (int)curSector[*addr + tryte(i)] << '\n';
                break;
            case two: // char
                if ((int)curSector[*addr + tryte(i)] < 255)
                    cout << (char)((int)curSector[*addr + tryte(i)]);
                else
                    cout << (int)curSector[*addr + tryte(i)] << '\n';
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
            if (sectors[*addr % tryte(27)] == nullptr)
            {
                throw runtime_error("Cannot access invalid memory sector");
            }
            curSector = sectors[*addr % tryte(27)];
        }
        else
        {
            curSector = mem;
        }
        break;

    default:
        cout << "Error during processing of instruction " << *instruc << '\n';
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
