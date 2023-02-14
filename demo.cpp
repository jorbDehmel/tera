#include "src/trit.hpp"
#include "src/tritcpu.hpp"
#include "src/tryteMath.hpp"
#include <iostream>

int main()
{
    tryte a(200);
    tryte b(220);

    cout << "Basic math:\n";
    cout << a + b << '\t' << (int)(a + b) << '\n';
    cout << b - a << '\t' << (int)(b - a) << '\n';

    cout << "Inc/dec operators:\n";
    for (int i = 0; i < 10; i++)
    {
        b++;
        a--;
        cout << a << '\t' << b << '\n';
    }

    cout << "Bitshift:\n";
    cout << (a << tryte(2)) << '\n';
    cout << (a >> tryte(2)) << '\n';

    cout << "Base 27 parsing:\n";
    auto v = trytesFromBase27("q1f");
    for (auto i : v)
    {
        cout << '\t' << i << '\t' << (int)i << '\n';
    }

    return 0;
}