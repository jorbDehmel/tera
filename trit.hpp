/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#ifndef TRIT_HPP
#define TRIT_HPP

#include <bitset>

// 2 bits each

#include <iostream>
using namespace std;

enum trit
{
    zero,
    one,
    two,
};

template <int size>
class TritBank
{
public:
    TritBank() : bank(0) {}
    TritBank(long long Data);

    void set(int Index, trit To);

    trit get(int Index) const;
    trit operator[](int Index) const
    {
        return get(Index);
    }

protected:
    bitset<size * 2> bank;
};

template <int size>
TritBank<size>::TritBank(long long Data)
{
}

template <int size>
void TritBank<size>::set(int Index, trit To)
{
    switch (To)
    {
    case zero:
        break;
    case one:
        break;
    case two:
        break;
    }
}

template <int size>
trit TritBank<size>::get(int Index) const
{
    if (!bank[Index * 2])
    {
        if (!bank[(Index * 2) + 1])
        {
            return zero;
        }
        else
        {
            return one;
        }
    }
    return two;
}

#endif
