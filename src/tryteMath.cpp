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

    if (by + toIncr[index] > 2)
    {
        incrTrit(toIncr, index + 1, one);
    }
    toIncr.set(index, (trit)((by + toIncr[index]) % 3));

    return;
}

void decrTrit(tryte &toDecr, const int &index, const trit &by)
{
    if (index > 8 || by == zero)
    {
        return;
    }

    if (toDecr[index] - by < 0)
    {
        decrTrit(toDecr, index + 1, one);
    }
    toDecr.set(index, (trit)((toDecr[index] - by + 3) % 3));

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
    tryte out(A);

    for (int i = 0; i < 9; i++)
    {
        decrTrit(out, i, B[i]);
    }

    return out;
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
        out.set((i + By) % 9, What[i]);
    }

    return out;
}

tryte operator>>(const tryte &What, const int &By)
{
    tryte out(0);
    for (int i = 0; i < 8; i++)
    {
        out.set(i, What[(i + By) % 9]);
    }

    return out;
}

tryte operator++(tryte &a)
{
    incrTrit(a, 0, one);
    return a;
}

tryte operator++(tryte &a, int)
{
    tryte out(a);
    incrTrit(a, 0, one);
    return out;
}

tryte operator--(tryte &a)
{
    decrTrit(a, 0, one);
    return a;
}

tryte operator--(tryte &a, int)
{
    tryte out(a);
    decrTrit(a, 0, one);
    return out;
}

tryte operator+=(tryte &a, tryte &by)
{
    a = (a + by);
    return a;
}

tryte operator-=(tryte &a, tryte &by)
{
    a = (a - by);
    return a;
}