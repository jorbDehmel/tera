/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include <iostream>
#include <fstream>
#include <chrono>
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
    string inputFileName = argv[1];

    // Look for .ter suffix on output
    if (inputFileName.size() < 5 || inputFileName.substr(inputFileName.size() - 5) != ".tera")
    {
        cout << tags::yellow_bold
             << "Warning! The proper file suffix for ternary compiled files is .tera\n"
             << tags::reset;
    }

    ifstream in(inputFileName);

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
        code += line + '\n';
    }
    in.close();

    // Decode bytes into trytes
    vector<tryte> parsed = rawParseTrytes(code);

    // Load trytes into memory
    TritCpu c;
    c.loadProgram(parsed);

#ifdef TIMER
    auto begin = chrono::high_resolution_clock::now();
    while (c.doInstr() == 0)
    {
        // This comment to make this loop less ugly
    }
    auto end = chrono::high_resolution_clock::now();
    long int ellapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
    cout << "Nanoseconds: " << ellapsed << '\n';

    cout << "Itemized:\n";
    for (auto item : instrTimes)
    {
        cout << "\tInstr: " << item.first << " av ns: " << item.second.first / item.second.second << '\n';
    }
#else
    while (c.doInstr() == 0)
    {
        // This comment to make this loop less ugly
    }
#endif
    return 0;
}
