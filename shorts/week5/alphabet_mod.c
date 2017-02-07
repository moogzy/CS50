#include <stdio.h>

#define LETTERSINALPHA 26

int main()
{
    int startofascii = 97;
    int hash_outcome;
    
    printf("%2s %2s\n", "Character", "Hash Outcome");
    for(int i = 1; i <= LETTERSINALPHA; i++)
    {
        hash_outcome = startofascii % 26;
        printf("%2c %9i\n", (char) startofascii, hash_outcome);
        startofascii++;
    }
}
