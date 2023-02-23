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
    string inputFileName = argv[1];
    string outputFileName = argv[2];

    // Look for .tasl suffix on input
    if (inputFileName.size() < 5 || inputFileName.substr(inputFileName.size() - 5) != ".tasl")
    {
        cout << tags::yellow_bold
             << "Warning! The proper file suffix for ternary assembly files is .tasl\n"
             << tags::reset;
    }

    // Look for .ter suffix on output
    if (outputFileName.size() < 5 || outputFileName.substr(outputFileName.size() - 5) != ".tera")
    {
        cout << tags::yellow_bold
             << "Warning! The proper file suffix for ternary compiled files is .tera\n"
             << tags::reset;
    }

    ifstream in(inputFileName);

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
    trit_assembly assembled;
    try
    {
        Assembler a;
        assembled = a.assemble(toAssemble);
    }
    catch (macro_error &e)
    {
        cout << tags::red_bold
             << "Error: Macro failed.\n"
             << e.what() << '\n'
             << tags::reset;
        return 6;
    }
    catch (runtime_error &e)
    {
        cout << tags::red_bold
             << "Error: Assembly failed.\n"
             << e.what() << '\n'
             << tags::reset;
        return 4;
    }
    catch (...)
    {
        cout << tags::red_bold
             << "Error: Fatal error occured.\n"
             << tags::reset;
        return 5;
    }

    cout << tags::green_bold
         << "Assembled.\n"
         << tags::reset;

    // Write to file
    ofstream out(outputFileName);

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
