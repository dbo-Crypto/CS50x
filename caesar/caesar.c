#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int cipher(string plain, int k);

int main(int argc, string argv[])
{
    int counter = 0;
    if (argc == 2) // Check if key is valid
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++) // Check if all key char are numbers
        {
            if (isdigit(argv[1][i]))
            {
                counter = counter + 0;
            }
            else
            {
                counter = counter + 1;
            }
        }
        if (counter == 0) // If OK, start program Cipher
        {
            int k = atoi(argv[1]);
            string plain = get_string("Plaintext:");
            cipher(plain, k);
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}


int cipher(string plain, int k) // Function cipher
{
    if (k > 26)
    {
        k = k % 26;
    }
    for (int i = 0, n = strlen(plain); i < n; i++) // Characte iteration
    {
        if (isalpha(plain[i])) // Check if character is alphanum
        {
            int ascii_code = plain[i] + k;
            if (ascii_code > 127) // To avoid to get out of ascii table
            {
                ascii_code = 127;
            }
            if (islower(plain[i])) // Check if character is lowercase
            {
                if (ascii_code >= 122)
                {
                    printf("plain is: %d\n", plain[i]);
                    plain[i] = 96 + k - (122 - plain[i]);
                }
                else
                {
                    plain[i] = plain[i] + k;
                }
            }
            else // Means character is uppercase
            {
                if (ascii_code >= 90)
                {
                    plain[i] = 64 + k - (90 - plain[i]);
                }
                else
                {
                    plain[i] = plain[i] + k;
                }
            }
        }
        else // Means that the character is special.
        {
            plain[i] = plain[i];
        }
    }
    printf("ciphertext: %s\n", plain);
    return 0;
}