/* 

Work out how many bottles of water are used based on 
user input of time spent in the shower.

Author: Adrian Arumugam
Date: May 31st 2016

*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt for user input of shower minutes
    // store in minutes.
    printf("Enter how many minutes your shower took:");
    int minutes = get_int();
    
    // Calculate how many gallons used
    // Gallon == 128 ounces of water
    // Average shower head outputs 1.5 gallons per minute.
    // == 1.5 x 128 = 192
    int gallons = minutes * 192;
    
    // Calculate how many bottles of water the gallons translates to
    // Typical size of bottled water == 16 ounces.
    int bottles = gallons / 16;
    
    // Print shower minutes and bottles used.
    printf("minutes: %d\n", minutes);
    printf("bottles: %d\n", bottles);
}