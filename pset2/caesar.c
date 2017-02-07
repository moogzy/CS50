/*

CS50x: Implementation of Caesar Cipher.

Usage:
    ./caesar <key-value>

Args:
    key-value: A positive integer

Author: Adrian Arumugam
Date: 17-Sep-2016

*/

#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[]){
    int keyval; // Initialize keyval
    
    // Fail fast if argument count is not 2.
    // This covers the actual command and first argument.
    if (argc != 2)
    {
        printf("Please provide a single argument for the key.\n");
        return 1;
    }
    
    // Convert string key-value to an interger for comparison
    keyval = atoi(argv[1]);
    
    // Fail fast if key-value meets this comparison.
    // If a non-integer is added atoi converts it to a < 1 value as well.
    if (keyval < 1)
    {
        printf("Please provide a positive number for the cipher key.\n");
        return 1;
    }
    // Lets get ready to rumble with the Caesar cipher.
    else
    {
        printf("plaintext:  ");
        char* plaintext = get_string(); // Prompt user string to encrypt
        int n = strlen(plaintext); // Counter for for loop
        char ciphertext[n]; // Initialize array the length of plaintext
        int cipherval; // Initialize cipher value
        int plainval; // Initialize plain value
        int subkeyval; // Initialize subtraction key
        const int numalpha = 26; // Number of characters in alphabet
        const int capitalend = 90; // End ascii code of A-Z
        const int lowercaseend = 122; // End ascii code of a-z
        keyval = keyval % numalpha; // Work out key-value modulo 26

        
        // Loop through the plaintext array which stores the string to encrypt.
        //
        // Iterating through each character of the string and performing the appropriate
        // actions.
        for (int i = 0; i < n; i++)
        {
            plainval = (int) plaintext[i]; // Convert the current char to an integer
            cipherval = plainval + keyval; // Default cipherval
            subkeyval = numalpha - keyval; // Default subtraction key
        
            // Alphabet data validaton - A-Z and a-z.
            //
            // If True then we potentially need to execute further
            // cipher value modification for correct encryption.
            if isalpha(plaintext[i])
            {
                // If the character is an uppercase character the following happens:
                //
                // 1. If cipherval is > the end of the uppercase alphabet(90)
                //    then cipherval is simply plaintext value minus the key value.
                // 2. Otherwise the cipherval is kept as the initial default cipher
                //    value.
                //
                // e.g BARFOO is encrypted as ONESBB with a key of 65
                //     66,65,82,79,79 > 79,78,69,83,66,66
                if isupper(plaintext[i])
                {
                    if (cipherval > capitalend)
                    {
                        cipherval = plainval - keyval;
                    }
                }
                // If the character is a lowercase character the following happens:
                //
                // 1. If cipherval is > than the end of the lowercase alphabet(122)
                //    then we check if the key-value is lower than the number of
                //    letters in the alphabet. If 'yes' then cipherval is plaintext
                //    value minus subtraction key value, if 'no' then cipherval is
                //    plaintext minus default modulo 26 key value.
                // 2. Otherwise cipherval is equal to plaintext value plus default
                //    modulo 26 key value.
                //
                // e.g barfoo encrypted as onesbb with a key of 65
                //     98,97,114,102,111,111 -> 111,110,101.115.98,98
                if islower(plaintext[i])
                {
                    if (cipherval > lowercaseend)
                    {
                        if (keyval < numalpha)
                        {
                            cipherval = plainval - subkeyval;
                        }
                        else
                        {
                            cipherval = plainval - keyval;
                        }
                    }
                    else
                    {
                        cipherval = plainval + keyval;
                    }                   
                }
            }
            // If the character is not A-Z or a-z then we don't encrypt
            // just copy the actual plaintext integer value to cipherval.
            else
            {
                cipherval = plainval;
            }
            // Store the cipher value in the array
            ciphertext[i] = (char) cipherval;
        }
        // Once the loop exits we can print out the cipher string.
        // This will be the encrypted string based on the key-value provided.
        printf("ciphertext: %s\n", ciphertext);
        return 0; // Return 0 to signal completion.
    }
}