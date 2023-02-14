/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "src/assembler.hpp"
#include "src/tags.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
using namespace std;

int main(const int argc, const char *argv[])
{
    if (argc != 3)
    {
        cout << tags::red_bold
             << "Invalid usage! Please provide an input and output file.\n"
             << tags::reset;
        return 1;
    }

    ifstream in(argv[1]);

    if (!in.is_open())
    {
        in.close();

        cout << tags::red_bold
             << "Error: Could not open input file.\n"
             << tags::reset;
        return 2;
    }

    // Get source code to assemble
    string toAssemble, line;
    while (getline(in, line))
    {
        toAssemble += line + '\n';
    }
    in.close();

    cout << tags::green_bold
         << "Assembling...\n"
         << tags::reset;

    // Assemble
    Assembler a;
    trit_assembly assembled = a.assemble(toAssemble);

    cout << tags::green_bold
         << "Assembled.\n"
         << tags::reset;

    // Write to file
    ofstream out(argv[2]);

    if (!out.is_open())
    {
        out.close();

        cout << tags::red_bold
             << "Error: Could not open output file.\n"
             << tags::reset;
        return 3;
    }

    out << assembled;
    out.close();

    return 0;
}
