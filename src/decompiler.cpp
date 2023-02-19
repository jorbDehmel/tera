/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "assembler.hpp"

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
    assert(argc == 2);

    string inputFile = argv[1];

    InstructionStealer temp;
    auto instructions = temp.invertedInstructions;
    auto variables = temp.invertedVariables;

    ifstream in(inputFile);
    assert(in.is_open());

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
            assert(instructions.count(curTryte) != 0);
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
        assert(out.is_open());

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