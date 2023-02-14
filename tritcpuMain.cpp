/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include <iostream>
#include <fstream>
#include "src/trit.hpp"
#include "src/tritcpu.hpp"
#include "src/tryteMath.hpp"
#include "src/tritcpu.hpp"
#include "src/tags.hpp"
using namespace std;

int main(const int argc, const char *argv[])
{
    if (argc != 2)
    {
        cout << tags::red_bold
             << "Invalid usage. You must provide an input file.\n"
             << tags::reset;
        return 1;
    }

    ifstream in(argv[1]);

    if (!in.is_open())
    {
        cout << tags::red_bold
             << "Error: Could not open input file.\n"
             << tags::reset;
        return 2;
    }

    // Load source code to string (raw bytes)
    string code, line;
    while (getline(in, line))
    {
        code += line;
    }
    in.close();

    // Decode bytes into trytes
    vector<tryte> parsed = rawParseTrytes(code);

    // Load trytes into memory
    TritCpu c;
    c.loadProgram(parsed);

    // Run
    while (c.doInstr() == 0)
    {
        cout << "tick\n";
    }

    cout << tags::green_bold
         << "Done.\n"
         << tags::reset;

    return 0;
}