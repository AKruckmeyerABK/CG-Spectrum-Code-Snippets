// QuickSortChrono.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <stdlib.h>

#define ARRAYSIZE 100

using namespace std;

void QuickSort(int size, int* array);
void QuickSort(int begin, int end, int* array);
void FillArray(int* array, int size);

uint32_t GetNanos()
{
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

int main()
{
    int array[ARRAYSIZE];

    srand(time(nullptr));
    FillArray(array, ARRAYSIZE);

    for (int i = 0; i < ARRAYSIZE; i++)
    {
        cout << array[i] << " ";
    }
   cout << endl;

    uint32_t StartNanos = GetNanos();
    QuickSort(ARRAYSIZE, array);
    uint32_t EndNanos = GetNanos();
    cout << "Time to complete QuickSort: " << EndNanos - StartNanos << " nanoseconds" << endl;

    for (int i = 0; i < ARRAYSIZE; i++)
    {
        cout << array[i] << " ";
    }
}

void QuickSort(int size, int* array)
{
   QuickSort(0, size-1, array);
}

void QuickSort(int begin, int end, int* array)
{
    int left = begin;
    int right = end; //swapping should start at the right, in case that the pivot is in the correct spot
    int pivot = array[end];
    int temp;

    if (left >= right)
        return;

    while (true)
    {
        //find values on the left of the array, that belong on the right of the pivot
        while (left < right && array[left] <= pivot)
        {
            left++;
        }
        //find vlaues on the right of the array that belong on the left of the pivot
        while (left < right && array[right] >= pivot)
        {
            right--;
        }
        //if the two crawlers don't meet up, swap the two values
        if (left < right)   
        {   
            temp = array[left];
            array[left] = array[right];
            array[right] = temp;
        }
        else
        {
            break;
        }
    }
    //swap with the pivot
    temp = array[right];
    array[right] = array[end];
    array[end] = temp;

    QuickSort(begin, left - 1, array);
    QuickSort(left + 1, end, array);
}

void FillArray(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % ARRAYSIZE;
    }
}