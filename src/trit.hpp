/*
Jordan "Jorb" Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

/*
Useful information for my definition of a tryte:
1 tryte = 9 trits (19'683 states)
1 kilotryte = 3^9 trytes
1 megatryte = 3^13 trytes
1 gigatryte = 3^19 trytes
*/

#ifndef TRIT_HPP
#define TRIT_HPP

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

enum trit
{
    zero,
    one,
    two,
};

class tryte
{
public:
    tryte();
    tryte(const tryte &Other);
    tryte(const short &What);

    tryte &operator=(const tryte &Other)
    {
        data = Other.data;
        return *this;
    }

    tryte &operator=(const short &Other)
    {
        data = Other;
        return *this;
    }

    operator int() const
    {
        return data;
    }

    trit operator[](const int &Index) const
    {
        return get(Index);
    }

    trit get(const unsigned int &Index) const;
    void set(const unsigned int &Index, const trit To);

    bool operator==(const tryte &other);
    bool operator!=(const tryte &other);

    bool operator<(const tryte &other);
    bool operator>(const tryte &other);

    bool operator<=(const tryte &other);
    bool operator>=(const tryte &other);

    tryte &operator+=(const tryte &by);
    tryte &operator-=(const tryte &by);

protected:
    short data = 0;
};

// Parses from encoded stringx
vector<tryte> trytesFromBase27(const string &Base27);

// Parses from raw chars, IE not encoded
vector<tryte> rawParseTrytes(const string &From);

string to_string(const tryte &What);
ostream &operator<<(ostream &strm, const tryte &T);

#endif
