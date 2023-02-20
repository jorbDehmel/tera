/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "stdMacros.hpp"

string print(Assembler &Caller, const string &Arg)
{
    string out;

    // Determine size to print
    unsigned int size = Arg.size();

    // Allocate appropriately sized variable
    out += ".__PRINT_TEMP " + to_string(size) + "\n";

    // Write to variable tryte by tryte
    for (int i = 0; i < size; i++)
    {
        out += "put ^__PRINT_TEMP." + to_string(i) + " ";

        if (Arg[i] == ' ')
        {
            out += "SPACE\n";
        }
        else if (Arg[i] == '\t')
        {
            out += "TAB\n";
        }
        else
        {
            out += string("-") + Arg[i] + "\n";
        }
    }

    // Out by the size of the variable
    out += "out __PRINT_TEMP " + to_string(size) + "\n";

    // Destruct the variable
    out += "~__PRINT_TEMP\n";

    return out;
}

string println(Assembler &Caller, const string &Arg)
{
    string out;

    // Determine size to print
    unsigned int size = Arg.size() + 1;

    // Allocate appropriately sized variable
    out += ".__PRINT_TEMP " + to_string(size) + "\n";

    // Write to variable tryte by tryte
    for (int i = 0; i + 1 < size; i++)
    {
        out += "put ^__PRINT_TEMP." + to_string(i) + " ";

        if (Arg[i] == ' ')
        {
            out += "SPACE\n";
        }
        else if (Arg[i] == '\t')
        {
            out += "TAB\n";
        }
        else
        {
            out += string("-") + Arg[i] + "\n";
        }
    }
    out += "put ^__PRINT_TEMP." + to_string(size - 1) + " ENDL\n";

    // Out by the size of the variable
    out += "out __PRINT_TEMP " + to_string(size) + "\n";

    // Destruct the variable
    out += "~__PRINT_TEMP\n";

    return out;
}

string req(Assembler &Caller, const string &Arg)
{
    string out;

    vector<string> vars;
    string temp;
    for (int i = 0; i < Arg.size(); i++)
    {
        if (Arg[i] == ' ')
        {
            vars.push_back(temp);
            temp = "";
        }
        else
        {
            temp += Arg[i];
        }
    }
    vars.push_back(temp);

    for (auto v : vars)
    {
        out += "incr " + v + " 0\n";
    }

    return out;
}
