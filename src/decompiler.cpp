/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "assembler.hpp"
#include "tags.hpp"

#include <cassert>
#include <iostream>
using namespace std;

// Dummy class for staying updated with assembler
class InstructionStealer : public Assembler
{
public:
    InstructionStealer() : Assembler()
    {
        for (auto i : instructions)
        {
            invertedInstructions[i.second] = i.first;
        }
        for (auto i : variables)
        {
            invertedVariables[i.second] = i.first;
        }
        return;
    }

    map<tryte, string> invertedInstructions;
    map<tryte, string> invertedVariables;
};

int main(const int argc, const char *argv[])
{
    if (argc != 2)
    {
        cout << tags::red_bold
             << "Error: Must provide an input file.\n"
             << tags::reset;
        return 1;
    }

    string inputFile = argv[1];
    if (inputFile.size() < 5 || inputFile.substr(inputFile.size() - 5) != ".tera")
    {
        cout << tags::yellow_bold
             << "Warning! The proper file suffix for ternary compiled files is .tera\n"
             << tags::reset;
    }

    InstructionStealer temp;
    auto instructions = temp.invertedInstructions;
    auto variables = temp.invertedVariables;

    ifstream in(inputFile);
    if (!in.is_open())
    {
        cout << tags::red_bold
             << "Error: Could not open input file.\n"
             << tags::reset;
        return 2;
    }

    trit_assembly tryteCode, line;
    while (!in.eof())
    {
        getline(in, line);
        tryteCode += line;
    }
    in.close();

    vector<tryte> assembly = rawParseTrytes(tryteCode);

    stringstream stringOut;

    int instrIndex = 0;
    for (tryte curTryte : assembly)
    {
        if (instrIndex % 3 == 0)
        {
            if (instructions.count(curTryte) == 0)
            {
                cout << tags::red_bold
                     << "Error: Non-instruction in instruction position.\n"
                     << tags::reset;
                return 3;
            }
            stringOut << instructions[curTryte];
        }
        else
        {
            stringOut << (int)curTryte;
        }

        instrIndex++;

        stringOut << '\t';
        if (instrIndex % 3 == 0)
        {
            stringOut << "//" << instrIndex - 3 << "\n";
        }
    }

    if (argc == 3)
    {
        string outputFile = argv[2];

        ofstream out(outputFile);
        if (!out.is_open())
        {
            cout << tags::red_bold
                 << "Error: Could not open output file.\n"
                 << tags::reset;
            return 4;
        }

        out << stringOut.str();
        out.close();

        cout << "Show output? [Y/n] ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            cout << stringOut.str() << '\n';
        }
    }
    else
    {
        cout << stringOut.str() << '\n';
    }

    return 0;
}
