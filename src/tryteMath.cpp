/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "tryteMath.hpp"

void incrTrit(tryte &toIncr, const int &index, const trit &by)
{
    if (index > 8 || by == zero)
    {
        return;
    }

    if ((int)by + (int)toIncr[index] > 2)
    {
        incrTrit(toIncr, index + 1, one);
    }
    toIncr.set(index, (trit)((int)by + (int)toIncr[index] % 2));

    return;
}

// Basic math operators
tryte operator+(const tryte &A, const tryte &B)
{
    tryte out(A);

    for (int i = 0; i < 9; i++)
    {
        incrTrit(out, i, B[i]);
    }

    return out;
}

tryte operator-(const tryte &A, const tryte &B)
{
    throw runtime_error("unimplemented");
    return tryte(0);
}

tryte operator*(const tryte &A, const tryte &B)
{
    throw runtime_error("unimplemented");
    return tryte(0);
}

tryte operator/(const tryte &A, const tryte &B)
{
    throw runtime_error("unimplemented");
    return tryte(0);
}

tryte operator%(const tryte &A, const tryte &B)
{
    throw runtime_error("unimplemented");
    return tryte(0);
}

// Bitshift operators
tryte operator<<(const tryte &What, const int &By)
{
    tryte out(0);
    for (int i = 0; i < 8; i++)
    {
        out.set(i + 1, What[i]);
    }

    return out;
}

tryte operator>>(const tryte &What, const int &By)
{
    tryte out(0);
    for (int i = 0; i < 8; i++)
    {
        out.set(i, What[i + 1]);
    }

    return out;
}

tryte &operator++(tryte &a)
{
    incrTrit(a, 0, one);
    return a;
}

tryte &operator++(tryte &a, int)
{
    tryte out(a);
    incrTrit(a, 0, one);
    return out;
}

tryte &operator--(tryte &a)
{
    throw runtime_error("unimplemented");
    tryte out(0);
    return out;
}

tryte &operator--(tryte &a, int)
{
    throw runtime_error("unimplemented");
    tryte out(0);
    return out;
}
