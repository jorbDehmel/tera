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

    // Buffer address variables (non-stack)
    instructions["INSTR"] = 0;
    instructions["CONT"] = 1;

    return;
}

/*
Symbol meanings:

+ access superscope variable (+VARNAME)
. variable declaration (.VAR 1)
~ stack pop (~VAR)
_ base 27 literal (_0qf)
/ comment (/ hi)
{ begin function ({FNNAME ...)
} end function and return (... }FNNAME)
! update call stack and call function (!FNNAME)

If a symbol doesn't match any of these, order is:
instruction
variable (current scope)
*/

string beforeFnCall;
string afterFnCall;

trit_assembly Assembler::assemble(const string &What)
{
    stringstream code;
    code << What;

    string instr, out;
    string prefix;

    while (!code.eof())
    {
        code >> instr;

        if (instructions.count(instr) != 0)
        {
            // Instruction
            out += encode(instructions[instr]);
        }
        else if (variables.count(prefix + instr) != 0)
        {
            // Variable (current scope)
            out += encode(variables[prefix + instr]);
        }
        else if (instr[0] == '+')
        {
            // Variable (superscope)
            string tempprefix = prefix;
            for (int i = 0; i < instr.size() && instr[i] == '+'; i++)
            {
                tempprefix = tempprefix.substr(1);
            }

            if (variables.count(tempprefix + instr) != 0)
            {
                // Variable (current scope)
                out += encode(variables[tempprefix + instr]);
            }
            else
            {
                throw runtime_error("No variable " + prefix + instr + " exists in superscope");
            }
        }
        else if (instr[0] == '.')
        {
            // Variable declaration
            int size = 0;
            code >> size;

            variables[instr.substr(1)] = firstOpenAddress;
            memStack.push(firstOpenAddress);
            firstOpenAddress += size;
        }
        else if (instr[0] == '~')
        {
            // Stack pop
            if (variables.count(instr.substr(1)) == 0 || memStack.top() != variables[instr.substr(1)])
            {
                throw runtime_error("Cannot pop a variable which is not on the top of the stack");
            }

            variables.erase(instr.substr(1));
            firstOpenAddress = memStack.top();
            memStack.pop();
        }
        else if (instr[0] == '_')
        {
            // Ternary literal
            vector<tryte> toInsert = trytesFromBase27(instr.substr(1));

            for (auto t : toInsert)
            {
                out += encode(t);
            }
        }
        else if (instr[0] == '{')
        {
            throw runtime_error("unimplemented");
        }
        else if (instr[0] == '!')
        {
            throw runtime_error("unimplemented");
        }
        else if (instr[0] == '/')
        {
            // Comment
            string garbage;
            getline(code, garbage);
        }
        else
        {
            // Decimal literal
            try
            {
                out += encode(tryte(stoi(instr)));
            }
            catch (invalid_argument e)
            {
                throw runtime_error("Invalid symbol '" + instr + "'");
            }
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
