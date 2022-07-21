// Factors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
    int factor;
    do
    {
        cout << "Enter a number: \n";
        cin >> factor;

        if (cin.fail())
        {
            cout << "Try again..." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
            break;
    } while (true);


    cout << "Factors for the number, " << factor << " are: ";
    for (int i = 1; i <= factor/2; i++)
    {
        if (factor % i == 0)
            cout << i << " ";
    }
    cout << factor << endl;
}