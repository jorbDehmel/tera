/*
Jordan Dehmel
jdehmel@outlook.com
github.com/jorbDehmel
2023 - present
MIT licence via mit-license.org held by author
*/

#include <chrono>
#include <iostream>
using namespace std;

int main(const int argc, const char *argv[])
{
    int num = 100'000;
    double average = 0;

    for (int i = 0; i < num; i++)
    {
        auto start = chrono::high_resolution_clock::now();
        cout << "Hello, World!\n";
        auto end = chrono::high_resolution_clock::now();
        int ellapsed = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        // cout << "Nanoseconds (cpp): " << ellapsed << '\n';

        average += ellapsed;
    }
    average /= num;

    system("clear");

    cout << "Average over " << num << " attempts: " << average << " nanoseconds\n";

    return 0;
}
