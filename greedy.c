/*

Handing back change via a greedy algorithm.

Greedy means to always use the least coins possible
to give back change. (Using the largest coins to the smallest)

Author: Adrian Arumugam
Date: 02/06/2016

*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Initialize values for coins
float quarter = 25;
float dime = 10;
float nickel = 5;
float penny = 1;

int main(void)
{
    // Initialize change to validate user input
    float change = -1;
    
    // Prompt user for input and store in change.
    // Repeat prompt if input is a negative value.
    //
    // Round change to avoid float imprecision so that 
    // we're rounded to the nearest dollar then multiply
    // user input by 100 to convert from dollars into cents.
    //
    // eg: 11.16 will be stored as 1116.00
    //     9.15 will be stored as 915.00 (without round function
    //     this would be 914.999939)
    while(change < 0)
    {
        printf("How much change is owed?\n");
        change = round(get_float() * 100);
    }
    
    // Initialize coin count
    int coins = 0;
    
    // While loops to validate the change remaining and perform and store
    // coin counting via division then calculate and store change remaining
    // via modulo
    while(change >= quarter)
    {
        coins += (int) change / (int) quarter;
        change = (int) change % (int) quarter;
    }
    while(change >= dime && change < quarter)
    {
        coins += (int) change / (int) dime;
        change = (int) change % (int) dime;
    }
    while(change >= nickel && change < dime)
    {
        coins += (int) change / (int) nickel;
        change = (int) change % (int) nickel;
    }
    while(change >= penny && change < nickel)
    {
        coins += (int) change / (int) penny;
        change = (int) change % (int) penny;
    }
    // Print out number of coins needed to hand back change via greedy
    // algorithm.
    printf("%d\n", coins);
}