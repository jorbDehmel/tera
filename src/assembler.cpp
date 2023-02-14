/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "assembler.hpp"

Assembler::Assembler()
{
    firstOpenAddress = tryte(27);

    // Build instruction table
    instructions["kill"] = kill;
    instructions["put"] = put;
    instructions["cpy"] = cpy;

    instructions["incr"] = incr;
    instructions["decr"] = decr;
    instructions["jump"] = jump;

    instructions["jumpBack"] = jumpBack;
    instructions["ifControl"] = ifControl;
    instructions["endif"] = endif;

    instructions["andEq"] = andEq;
    instructions["andNeq"] = andNeq;
    instructions["andLess"] = andLess;

    instructions["andGreater"] = andGreater;
    instructions["orEq"] = orEq;
    instructions["orNeq"] = orNeq;

    instructions["orLess"] = orLess;
    instructions["orGreater"] = orGreater;
    instructions["out"] = out;

    instructions["inp"] = inp;
    instructions["sector"] = sector;

    return;
}

trit_assembly Assembler::assemble(const string &What)
{
    stringstream code;
    code << What;

    string instr, out;

    while (!code.eof())
    {
        code >> instr;

        if (instructions.count(instr) != 0)
        {
            out += encode(instructions[instr]);
        }
        else if (functions.count(instr) != 0)
        {
            out += assemble(functions[instr]);
        }
        else if (variables.count(instr) != 0)
        {
            out += encode(variables[instr]);
        }
        else
        {
            // decimal literal
            out += encode(tryte(stoi(instr)));
        }

        if (instr == "kill")
        {
            break;
        }
    }

    return out;
}

trit_assembly Assembler::encode(const tryte &What)
{
    // encode as 3 chars
    trit_assembly out;

    out += (char)((int)((What >> tryte(6)) % tryte(27)));
    out += (char)((int)((What >> tryte(3)) % tryte(27)));
    out += (char)((int)(What % tryte(27)));

    return out;
}
