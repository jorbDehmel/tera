/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include "trit.hpp"

tryte::tryte()
{
    data = 0;
    return;
}

tryte::tryte(const tryte &Other)
{
    data = Other.data;
    return;
}

tryte::tryte(const short &What)
{
    data = What;
    return;
}

trit tryte::get(const unsigned int &Index) const
{
    if (Index > 8)
    {
        throw runtime_error("Invalid index! (Trytes have 9 trits)");
    }

    int res = (data % (int)pow(3, Index + 1)) / pow(3, Index);

    switch (res)
    {
    case 0:
        return zero;
        break;
    case 1:
        return one;
        break;
    case 2:
        return two;
        break;
    }

    return zero;
}

void tryte::set(const unsigned int &Index, const trit To)
{
    if (Index > 8)
    {
        throw runtime_error("Invalid index! (Trytes have 9 trits)");
    }

    switch (get(Index))
    {
    case zero:
        break;
    case one:
        data -= pow(3, Index);
        break;
    case two:
        data -= 2 * pow(3, Index);
        break;
    }

    data += To * pow(3, Index);
}

bool tryte::operator==(const tryte &other)
{
    for (int i = 0; i < 9; i++)
    {
        if ((*this)[i] != other[i])
        {
            return false;
        }
    }
    return true;
}

bool tryte::operator!=(const tryte &other)
{
    for (int i = 0; i < 9; i++)
    {
        if ((*this)[i] != other[i])
        {
            return true;
        }
    }
    return false;
}

bool tryte::operator<(const tryte &other)
{
    for (int i = 8; i >= 0; i--)
    {
        if ((*this)[i] < other[i])
        {
            return true;
        }
        else if ((*this)[i] > other[i])
        {
            return false;
        }
    }
    return false;
}

bool tryte::operator>(const tryte &other)
{
    for (int i = 8; i >= 0; i--)
    {
        if ((*this)[i] > other[i])
        {
            return true;
        }
        else if ((*this)[i] < other[i])
        {
            return false;
        }
    }
    return false;
}

bool tryte::operator<=(const tryte &other)
{
    for (int i = 8; i >= 0; i--)
    {
        if ((*this)[i] < other[i])
        {
            return true;
        }
        else if ((*this)[i] > other[i])
        {
            return false;
        }
    }
    return true;
}

bool tryte::operator>=(const tryte &other)
{
    for (int i = 8; i >= 0; i--)
    {
        if ((*this)[i] > other[i])
        {
            return true;
        }
        else if ((*this)[i] < other[i])
        {
            return false;
        }
    }
    return true;
}

tryte &tryte::operator+=(const tryte &by)
{
    data += by.data;
    return *this;
}

tryte &tryte::operator-=(const tryte &by)
{
    data -= by.data;
    return *this;
}

vector<tryte> trytesFromBase27(const string &Base27)
{
    string key = "0123456789abcdefghijklmnopq";
    vector<tryte> out;

    for (int i = 0; i < Base27.size();)
    {
        // Convert to decimal
        short dec = key.find(Base27[i]) * 27 * 27;
        i++;

        dec += (key.find(Base27[i]) * 27);
        i++;

        dec += key.find(Base27[i]);
        i++;

        // Append ternary equivolent of decimal
        out.push_back(tryte(dec));
    }

    return out;
}

vector<tryte> rawParseTrytes(const string &From)
{
    vector<tryte> out;

    for (int i = 0; i < From.size(); i += 3)
    {
        if (From[i + 2] > 27 || From[i + 1] > 27 || From[i] > 27)
        {
            throw runtime_error("Could not parse (char > 27)");
        }

        // Convert to decimal
        short dec = From[i + 2] + (From[i + 1] * 27) + (From[i] * 27 * 27);

        // Append ternary equivolent of decimal
        out.push_back(tryte(dec));
    }

    return out;
}

string to_string(const tryte &What)
{
    string out = "";
    for (int i = 0; i < 9; i++)
    {
        switch (What[i])
        {
        case zero:
            out = "0" + out;
            break;
        case one:
            out = "1" + out;
            break;
        case two:
            out = "2" + out;
            break;
        }

        if (i == 2 || i == 5)
        {
            out = "'" + out;
        }
    }

    return "0t" + out;
}

ostream &operator<<(ostream &strm, const tryte &T)
{
    strm << to_string(T);
    return strm;
}
