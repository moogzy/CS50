/*

Print initials from name entered.

Author: Adrian Arumugam
Date: 17-Sept-2016

*/

#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// Function to prompt for the users name.
string PromptForName(void){
    return get_string();
}

int main(void){
    char* name = PromptForName();
    const char delim = ' '; // Space delimiter to split string
    char *word;
    char initials[5]; // Initialize the array to 5, limits name size.
    int counter = 0;
    
    // Parse string(name), delimit with ' ' and return
    // a pointer to the first token found.
    word = strtok(name, &delim);
    
    // Loop through tokens which are null terminated(/0)
    //
    // 1. Assign initial char to array and capatilize.
    // 2. Increment counter.
    // 3. Call strtok again to return pointer to next token.
    while( word != NULL ){ 
        initials[counter] = toupper(word[0]);
        counter++;
        // Subsequent calls to strtok should use 'NULL' as the string.
        // Once all tokens have been looped through 'NULL' will
        // be returned which will end the while loop.
        word = strtok(NULL, &delim);
    }
    // We now have all initial chars stored in an array.
    //
    // Let's print them out!
    printf("%s\n", initials);
}