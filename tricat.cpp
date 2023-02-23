/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include <iostream>
#include <fstream>
#include <string>
#include "src/tags.hpp"
#include "src/trit.hpp"
#include "src/tryteMath.hpp"
using namespace std;

int main(const int argc, const char *argv[])
{
    if (argc != 2)
    {
        cout << tags::red_bold
             << "Invalid syntax.\n"
             << tags::reset;
        return 1;
    }

    ifstream in(argv[1]);
    if (!in.is_open())
    {
        cout << tags::red_bold
             << "Could not open file.\n"
             << tags::reset;
        return 2;
    }

    string text, line;
    while (getline(in, line))
    {
        text += line;
    }
    in.close();

    auto out = rawParseTrytes(text);

    for (int i = 0; i < (int)out.size(); i++)
    {
        if (i % 3 == 0)
        {
            if (i != 0)
            {
                cout << '\n';
            }
            cout << i << "\t|\t";
        }

        cout << out[i] << "\t\t";
    }
    cout << '\n'
         << "Size: " << out.size() << " trytes\n";

    return 0;
}
