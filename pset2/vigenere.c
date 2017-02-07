/*

CS50x: Implementation of Vigenere Cipher.

Usage:
    ./vigenere <secret-key>

Args:
    secret-key: A word used to encrypt the plaintext.

Author: Adrian Arumugam
Date: 23-Sep-2016

*/

#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[]){
    
    // Fail fast if argument count is not 2.
    // This covers the actual command and first argument.
    if (argc != 2)
    {
        printf("Please provide a single argument for the key.\n");
        return 1;
    }
    
    char* keyword = argv[1]; // Initialize keyword
    int c = strlen(keyword);
    
    // Loop through the characters to identify if they are
    // any disallowed characters.
    for (int i = 0; i < c; i++)
    {
        if isalpha(keyword[i])
        {
            continue;
        }
        else
        {
            printf("Please enter a word for the secret key.\n");
            return 1;
        }
    }
    
    // Lets get ready to rumble with the Vigenere cipher.
    
    printf("plaintext:  ");
    char* plaintext = get_string(); // Prompt user string to encrypt
    int n = strlen(plaintext); // Counter for for loop
    char ciphertext[n + 1]; // Initialize array the length of plaintext + 1
    int cipherval; // Initialize cipher value
    int plainval; // Initialize plain value
    int subkeyval; // Initialize subtraction key
    int keyval; // Initialize to store value for key
    int j = 0; // Counter for key char
    const int numalpha = 26; // Number of characters in alphabet
    const int asciinum = 65; // Used to determing correct key value
    const int capitalend = 90; // End ascii code of A-Z
    const int lowercaseend = 122; // End ascii code of a-z
    
    // Loop through the plaintext array which stores the string to encrypt.
    //
    // Iterating through each character of the string and performing the appropriate
    // actions.

    for (int i = 0; i <= n; i++)
    {
        j = j % strlen(keyword);
        plainval = (int) plaintext[i]; // Convert the current char to an integer
        keyval = (int) toupper(keyword[j]) - asciinum; // Uppercase and lower case treated the same. This determines value(0-25)
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
            //    then we look at whether the keyval is equal to [Zz] if yes
            //    then cipherval plainval - subkeyval(which would be 1 in this instance)
            // 2. Otherwise the cipherval is plainval - keyval.
            //
            // e.g BARFOO is encrypted as CAQGON with a key of BAZ
            //     66,65,82,79,79 > 67,65,81,79,78
            if isupper(plaintext[i])
            {
                if (cipherval > capitalend)
                {
                    if (keyval != numalpha - 1)
                    {
                        cipherval = plainval - keyval;
                    }
                    else
                    {
                        cipherval = plainval - subkeyval;
                    }
                }
            }
            // If the character is a lowercase character the following happens:
            //
            // 1. If cipherval is > than the end of the lowercase alphabet(122)
            //    then cipherval is equal to plainval - subkeyval.
            // 2. Otherwise cipherval is equal to plaintext val - keyval.
            //
            // e.g barfoo encrypted as caqgon with a key of BAZ
            //     98,97,114,102,111,111 -> 99,97,113,103,111,110
            if islower(plaintext[i])
            {
                if (cipherval > lowercaseend)
                {
                    cipherval = plainval - subkeyval;
                }
                else
                {
                    cipherval = plainval + keyval;
                }
            }
            j++;
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
    // This will be the encrypted string based on the secret key provided.
    printf("ciphertext: %s\n", ciphertext);
    return 0; // Return 0 to signal completion.
}