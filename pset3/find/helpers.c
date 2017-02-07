/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 * Uses Binary(bi-section) search - O(n log n).
 * 
 */
bool search(int value, int values[], int n)
{
    int start = 0;
    int end = n;
    int mp = n / 2;
    bool exists = false;
    
    // Simple data validation to ensure midpoint is valid.
    //
    // If validaton passes then use binary(bi-section) search
    // to find a given value in an array.
    while (mp >= 0)
    {
        /* When the midpoint value is greater, set end to midpoint.
         * and the calculate the new midpoint.
         *
         * If mp is 0 or equal to n -1 then set the mp to -1 to break
         * out of the while loop. */
        if (values[mp] > value)
        {
            if (mp == 0 || mp == (n - 1))
            {
                mp = -1;
            }
            else
            {
                end = mp;
                mp = (start + end) / 2;
            }
        }
        /* When the midpoint is lower then calculate new midpoint
         * by adding end to mp and dividing by 2.
         * 
         * If mp is 0 or equal to n -1 then set the mp to -1 to break
         * out of the while loop. */
        else if (values[mp] < value)
        {
            if (mp == 0 || mp == (n - 1))
            {
                mp = -1;
            }
            else
            {
                mp = (end + mp) / 2;
            }
        }
        // Woohoo we found the value.
        //
        // Break from the loop.
        else if (values[mp] == value)
        {
            exists = true;
            break;
        }
        // Ba-bum... no bingo, couldn't find the value in the array.
        else
        {
            exists = false;
            break;
        }
    }
    return exists;
}


/**
 * Sorts array of n values.
 * 
 * Uses Bubble Sort.
 * 
 * Arrays are passed by reference not by value.
 * Therefore the array will be destructively sorted.
 * (i.e sorted in place, there is no copy of the original array)
 */
void sort(int values[], int n)
{
    int nosorts = 0;
    int j;
    int k;
    int store;
    int i = 0;
    
    // Implmentation of bubble sort to sort the array provided.
    //
    // If nosorts is equal to the number of elements in the array
    // then we have passed through the full array without making
    // any sorting changes and proven the array is sorted.
    while (nosorts != n)
    {
        // If we reach the end of the array, return to the start of the
        // array by setting i == 0.
        //
        // We need a full pass through the array without any sorting
        // changes to confim that we have a sorted array.
        if (i == n - 1)
        {
            i = 0;
        }
       
        // If we pass the initial validation check then continue with
        // the Bubble Sort algorithm.
        j = values[i];
        k = values[i + 1];
        
        // If current array value > current array value + 1 then
        // swap the values around and set nosorts to 0.
        //
        // Bigger values will bubble their way to the right of an array,
        // smaller values will bubble their way to the left of an array.
        //
        //
        // Else if no sorting change is made increment the nosorts counter.
        if (j > k)
        {
          store = j;
          values[i] = k;
          values [i + 1] = store;
          nosorts = 0;
        }
        else
        {
            nosorts++;
        }
        // This counter keeps us cycling through the array.
        i++;
    }
    // Once sorted return.
    return;
}

/**
 * Returns true if value is in array of n values, else false.
 * (Uses Linear Seach O(n))
 */
bool naiveSearch(int value, int values[], int n)
{
    // Simple data validation to determine if values is a postive integer.
    // Otherwise return 'false' immediately.
    if (value > 0)
    {
        // Default return value.
        bool exists = false;
        
        // Use linear search to cycle through each item in the array 'values'
        // based on the size of the array [n].
        //
        // Compare value to values[i] if a match is found return 'true'
        // and break from the linear search loop.
        //
        // If no match is found then return 'false'
        for (int i = 0; i < n ; i++)
        {
            if (value == values[i])
            {
                exists = true;
                return exists;
                break;
            }
        }
        return exists;
        
    }
    else
    {
      return false;
    }
}