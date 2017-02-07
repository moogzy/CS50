/*

Print the Super Mario Pyramid from world 1-1 in Nintendo’s Super Mario Brothers

Author: Adrian Arumugam
Date: 01-06-2016

*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Initialize local variable. Needs to be < 0 as we accept 0 as a valid
    // input which prints nothing.
    int height = -1;
    
    // While loop to validate user input of the height variable
    // Must be >=0 and <=23. No negative integers.
    while((height < 0) || (height > 23))
    {
        printf("Height: ");
        height = get_int();
    }
    
    // Counter initialization
    int i = 1;
    // Initialize the hash char array to store no more than 23 characters
    char hash[23] = "#";
    // Initialize width to handle right aligning the pyramid.
    int width = height + 1;
    
    // Where the magic happens - concatenation through each loop iteration
    // prints out the pyramid structure with right alignment handled in the 
    // printf statement.
    while(i <= height)
    {
        strcat(hash, "#");
        printf("%*s\n", width, hash);
        i++;
    }
}