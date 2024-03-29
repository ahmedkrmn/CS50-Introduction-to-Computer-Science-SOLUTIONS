/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

//WARNING : If both numbers are equal this function will set one of them to ZERO
//Inputs are passed using "C style pass-by-reference"
void swap(int *a,int *b)
{
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if(n<0) return false;
    int start = 0 ,end = n-1;
    while(start<=end)
    {
        int mid = (start + end)/2;
        if(values[mid] > value)
            end = mid - 1;
        else if(values[mid] < value)
            start = mid + 1;
        else
            return true;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n) //Counting sort
{

    int arr[65536]={0};
    for(int i = 0 ; i < n ; i++)
    {
        arr[values[i]]++;
    }
    int index=0;
    for(int i = 0 ; i < 65536 ; i++)
    {
        while(arr[i]--)
        {
            values[index]=i;
            index++;
        }
    }
    return;
}

// void bubble_sort(int arr[] , int n)
// {
//     for (int i = 0; i < n-1; ++i)
//     {
//         bool swapped = false;
//         for (int i = 0; i < n-1; ++i)
//         {
//             if(arr[i]>arr[i+1])
//                 {
//                     swap(arr+i,arr+i+1);
//                     swapped = true;
//                 }

//         }
//         if(!swapped) return;
//     }
//     return;
// }

// void selection_sort (int arr[] , int n)
// {
//     for (int i = 0; i < n; ++i)
//     {
//         int min = i;
//         for (int j = i; j < n; ++j)
//         {
//             if(arr[j]<arr[min]) min = j;
//         }
//         if(arr[i]!=arr[min])
//             swap(arr+i,arr+min);
//     }
//     return;
// }


