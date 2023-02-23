/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "tryteMath.hpp"

// Basic math operators
tryte operator+(const tryte &A, const tryte &B)
{
    tryte out(A.data + B.data);
    return out;
}

tryte operator-(const tryte &A, const tryte &B)
{
    tryte out(A.data - B.data);
    return out;
}

tryte operator*(const tryte &A, const tryte &B)
{
    tryte out(A.data * B.data);
    return out;
}

tryte operator/(const tryte &A, const tryte &B)
{
    tryte out(A.data / B.data);
    return out;
}

tryte operator%(const tryte &A, const tryte &B)
{
    tryte temp(A.data % B.data);
    return temp;
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
        if (i + By < 9)
            out.set(i, What[i + By]);
    }

    return out;
}

tryte operator++(tryte &a)
{
    a.data++;
    return a;
}

tryte operator++(tryte &a, int)
{
    tryte out(a);
    a.data++;
    return out;
}

tryte operator--(tryte &a)
{
    a.data--;
    return a;
}

tryte operator--(tryte &a, int)
{
    tryte out(a);
    a.data--;
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

tryte operator*=(tryte &A, const tryte &B)
{
    A = (A * B);
    return A;
}

tryte operator/=(tryte &A, const tryte &B)
{
    A = (A / B);
    return A;
}
