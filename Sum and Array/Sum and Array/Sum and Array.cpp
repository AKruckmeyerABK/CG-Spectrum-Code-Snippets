// Sum and Array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
    float a, b, c;
    cout << "Please enter 3 numbers, seperated by spaces:\n";
    cin >> a;
    cin >> b;
    cin >> c;

    cout << "Sum of the numbers: " << a << " + " << b << " + " << c << " = " << a + b + c << "\n";
    cout << "Average of  the numbers: (" << a << " + " << b << " + " << c << ")/3 = " << (a + b + c) / 3 << "\n";
}
