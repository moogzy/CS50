#include <stdio.h>

/* 
  CS50x: Week 4 Shorts - Collatz challenge
  
  Write a recursive function that utilizes the Collatz Conjecture.
  https://en.wikipedia.org/wiki/Collatz_conjecture
  
  Author: Adrian Arumugam
  Date: 2016-01-08
  
*/

int collatz(int n)
{
    // Base case.
    if (n == 1)
        return 0;
        
    // Even numbers.
    else if ((n % 2) == 0)
        return 1 + collatz(n / 2);
    
    // Odd numbers.
    else
        return 1 + collatz((3 * n) + 1);
}

int main(void)
{
    int numbers[11] = {1,2,3,4,5,6,7,8,15,27,50};
    
    for(int i = 0; i < 11; i++)
    {
        int steps = collatz(numbers[i]);
        printf("Steps to reach 1 from %i: %i\n", numbers[i], steps);
    }
}

