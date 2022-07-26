// I know how to use pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
    cout << "Enter 2 values for a and b" << endl;

    int a, b;
    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    int* ptrA = &a;
    int* ptrB = &b;

    cout << "prtA points to a. *prtA = " << *ptrA << endl;
    cout << "prtB points to b. *prtB = " << *ptrB << endl;
}
