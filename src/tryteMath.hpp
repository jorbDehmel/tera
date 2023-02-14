/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#ifndef TRYTEMATH_HPP
#define TRYTEMATH_HPP

#include "trit.hpp"

// Basic math operators
tryte operator+(const tryte &A, const tryte &B);
tryte operator-(const tryte &A, const tryte &B);
tryte operator*(const tryte &A, const tryte &B);
tryte operator/(const tryte &A, const tryte &B);
tryte operator%(const tryte &A, const tryte &B);

// Bitshift operators
tryte operator<<(const tryte &What, const int &By);
tryte operator>>(const tryte &What, const int &By);

// Increment operators
tryte &operator++(tryte &a);      // pre
tryte &operator++(tryte &a, int); // post
tryte &operator--(tryte &a);      // pre
tryte &operator--(tryte &a, int); // post

#endif
