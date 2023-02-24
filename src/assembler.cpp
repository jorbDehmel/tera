/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "assembler.hpp"

#define INSTRSTART (MEMSIZE * 2 / 3)
#define CHAR_OFFSET 13'122

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

    instructions["andEqV"] = andEqV;
    instructions["andNeqV"] = andNeqV;
    instructions["andLessV"] = andLessV;

    instructions["andGreaterV"] = andGreaterV;
    instructions["orEqV"] = orEqV;
    instructions["orNeqV"] = orNeqV;

    instructions["orLessV"] = orLessV;
    instructions["orGreaterV"] = orGreaterV;
    instructions["out"] = out;

    instructions["inp"] = inp;
    instructions["sector"] = sector;
    instructions["addV"] = addV;

    instructions["subtractV"] = subtractV;
    instructions["multV"] = multV;
    instructions["divV"] = divV;

    instructions["modV"] = modV;
    instructions["ifNever"] = ifNever;

    // Buffer address variables (non-stack)
    variables["INSTR"] = var(0, 1);
    variables["CONT"] = var(1, 1);
    variables["RET"] = var(2, 1);

    // Convenience variables
    variables["ENDL"] = var('\n' + CHAR_OFFSET, 1);
    variables["SPACE"] = var(' ' + CHAR_OFFSET, 1);
    variables["TAB"] = var('\t' + CHAR_OFFSET, 1);

    // No argument instructions
    noArgs.insert("kill");
    noArgs.insert("ifControl");
    noArgs.insert("ifNever");
    noArgs.insert("endif");

    // Include standard macros
    macros["print"] = print;
    macros["println"] = println;
    macros["req"] = req;

    macros["cpy"] = copyVars;
    macros["zero"] = zeroOut;

    return;
}

string handleScope(const string &Prefix, const string &VarName)
{
    if (VarName[0] == '+')
    {
        string tempname = Prefix + VarName;
        for (int i = 0; i < (int)VarName.size() && VarName[i] == '+'; i++)
        {
            if (tempname[0] != '+')
            {
                throw runtime_error("Base scope has no superscope");
            }

            tempname = tempname.substr(2);
        }

        return tempname;
    }
    else if (VarName[0] == '*')
    {
        return VarName.substr(1);
    }
    else
    {
        return Prefix + VarName;
    }
}

trit_assembly Assembler::assemble(const string &What)
{
    cout << "Premacro pass...\n";
    stringstream temp;
    temp << What;

    string line;
    while (getline(temp, line))
    {
        while (line[0] == ' ' || line[0] == '\t')
        {
            line = line.substr(1);
        }

        if (line[0] == '.')
        {
            stringstream extract;
            extract << line.substr(1);

            int size;
            string name;
            extract >> name >> size;

            variables[name] = var(tryte(0), tryte(size));
        }
    }

    string postMacro = What;
    string instr;

    int macroPass = 0;
    do
    {
        // Load variables for generalized passes
        stringstream preMacro;
        preMacro << postMacro;
        postMacro = "";

        // Macro replacement pass
        cout << "Handling macros (pass " << macroPass++ << ")\n";
        while (!preMacro.eof())
        {
            getline(preMacro, instr);
            while (instr[0] == ' ' || instr[0] == '\t')
            {
                instr = instr.substr(1);
            }

            if (instr[0] == '#')
            {
                string name;
                for (int i = 1; i < (int)instr.size() && instr[i] != ' '; i++)
                {
                    name += instr[i];
                }

                if (macros.count(name) != 0)
                {
                    string arg = instr.substr(name.size() + 2);
                    postMacro += macros[name](*this, arg) + '\t';
                }
                else
                {
                    throw runtime_error("Unknown macro '" + instr.substr(1) + "'");
                }
            }
            else
            {
                postMacro += instr + '\n';
            }
        }
    } while (postMacro.find('#') != string::npos);

    // Compilation pass
    stringstream code;
    code << postMacro;

    cout << "Assembling...\n";

    string out;
    string prefix;

    while (!code.eof())
    {
        code >> instr;

        if (instructions.count(instr) != 0)
        {
            // Instruction
            out += encode(instructions[instr]);

            // Take care of no argument instructions
            if (noArgs.count(instr) != 0)
            {
                out += encode(tryte(0)) + encode(tryte(0));
            }
        }
        else if (functions.count(instr) != 0)
        {
            // Function
            cout << "Function " << instr << " maps to address " << functions[instr] << '\n';
            out += encode(functions[instr]);
        }
        else if (variables.count(handleScope(prefix, instr)) != 0)
        {
            // Variable (current scope)
            out += encode(variables[handleScope(prefix, instr)].first);
        }
        else if (instr[0] == '^')
        {
            string arg = handleScope(prefix, instr.substr(1));

            string name;
            int by;

            int ind = 0;
            while (arg[ind] != '.')
            {
                name += arg[ind];
                ind++;

                if (ind >= (int)arg.size())
                {
                    throw runtime_error("Invalid usage of pointer arithmatic operator");
                }
            }

            by = stoi(arg.substr(ind + 1));

            // Pointer arithmatic
            if (variables.count(name) == 0)
            {
                throw runtime_error("Unknown variable '" + name + "'");
            }
            else
            {
                if (by >= 0)
                {
                    out += encode(variables[name].first + tryte(by));
                }
                else
                {
                    // Trytes do not natively support negatives
                    out += encode(variables[name].first - tryte(-by));
                }
            }
        }
        else if (instr[0] == '$')
        {
            string name = handleScope(prefix, instr.substr(1));
            if (variables.count(name) == 0)
            {
                throw runtime_error("No variable '" + name + "' found.");
            }

            out += encode(variables[name].second);
        }
        else if (instr[0] == '.')
        {
            // Variable declaration
            int size = 0;
            code >> size;

            variables[prefix + instr.substr(1)] = var(firstOpenAddress, tryte(size));

            memStack.push(firstOpenAddress);
            firstOpenAddress += size;
        }
        else if (instr[0] == '~')
        {
            // Stack pop
            if (variables.count(prefix + instr.substr(1)) == 0 || memStack.top() != variables[prefix + instr.substr(1)].first)
            {
                throw runtime_error("Cannot pop a variable which is not on the top of the stack");
            }

            variables.erase(prefix + instr.substr(1));
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
        else if (instr[0] == '-')
        {
            tryte toInsert((int)instr[1] + CHAR_OFFSET);
            out += encode(toInsert);
        }
        else if (instr[0] == '{')
        {
            // Call CPU's integrated function jumper
            out += encode(ifNever) + encode(tryte(0)) + encode(tryte(0));

            string name = instr.substr(1);
            functions[name] = (INSTRSTART + out.size() / 3);
            prefix = "+" + prefix;

            cout << "Started function " << name << '\n';
        }
        else if (instr[0] == '}')
        {
            if (prefix == "")
            {
                throw runtime_error("Error: Cannot end global scope");
            }

            cout << "Ended function\n";

            prefix = prefix.substr(1);

            // End CPU's integrated function jumper
            out += encode(endif) + encode(tryte(0)) + encode(tryte(0));
        }
        else if (instr[0] == '!')
        {
            string name = instr.substr(1);
            if (name == "return")
            {
                vector<tryte> toInsert = {
                    cpy, RET, INSTR};
                for (auto t : toInsert)
                {
                    out += encode(t);
                }
            }
            else if (functions.count(name) == 0)
            {
                throw runtime_error("Error: Undeclared function " + name);
            }
            else
            {
                // .OLD_RET 1 /unnamed compile-time var
                tryte oldRet = firstOpenAddress;
                memStack.push(firstOpenAddress);
                firstOpenAddress += 1; // since size is 1 tryte

                // cpy RET OLD_RET
                // cpy INSTR RET
                // incr RET 6
                vector<tryte> toInsert = {
                    cpy, RET, oldRet,
                    cpy, INSTR, RET,
                    incr, RET, tryte(6)};
                for (auto t : toInsert)
                {
                    out += encode(t);
                }

                // Jump to fn command
                out += encode(tryte(jump));
                out += encode(functions[name]);
                out += encode(tryte(0));

                // cpy OLD_RET RET
                toInsert = {
                    cpy, oldRet, tryte(2)};
                for (auto t : toInsert)
                {
                    out += encode(t);
                }

                // ~OLD_RET
                firstOpenAddress = memStack.top();
                memStack.pop();
            }
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
            catch (invalid_argument &e)
            {
                throw runtime_error("Invalid symbol '" + prefix + instr + "'");
            }
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
