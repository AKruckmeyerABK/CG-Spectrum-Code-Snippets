// leapyear.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>

using namespace std;

bool LeapYearCheck(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0 && year % 400 != 0) return false;
        return true;
    }
    return false;
}

int main()
{
    /*
    time_t t = time(0);
    struct tm* timeStruct = localtime(&t);
    if (LeapYearCheck(timeStruct->tm_year))
        cout << "The current year " << (timeStruct->tm_year) << " is a leap year." << endl;
    else
        cout << "The current year " << (timeStruct->tm_year) << " is not a leap year." << endl;;*/

    int year;
    cout << "Gimme a year:" << endl;
    cin >> year;
    if (LeapYearCheck(year))
        cout << "The year " << (year) << " is a leap year." << endl;
    else
        cout << "The year " << (year) << " is not a leap year." << endl;;
}