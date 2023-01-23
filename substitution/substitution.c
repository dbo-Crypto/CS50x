#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int substitution(string plain, string key);
int letter_position(char plain);
string key_validation(string key, int argc);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc == 2 && strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        // Key validity testing
        int count = 0;
        int counter = 0;
        int res = 0;
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i])) // Check if all character are alphabetical
            {
                count = count + 0;
            }
            else
            {
                count = count + 1;
            }
        }
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            counter = 1;
            for (int j = i + 1; j < strlen(argv[1]); j++) // check for duplicates
            {
                if (argv[1][i] == argv[1][j] && argv[1][i] != ' ')
                {
                    counter++;
                    argv[1][j] = '0';
                }
            }
            if (counter > 1 && argv[1][i] != '0')
            {
                res = counter + 1;
            }
            else
            {
                res = res + 0;
            }
        }
        if (count + res == 0) // Final check for Key validity, if OK start substitution program.
        {
            string plaintext = get_string("plaintext: ");
            substitution(plaintext, argv[1]);
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int substitution(string plain, string key) // Substitution function
{
    for (int i = 0, n = strlen(plain); i < n; i++) // For each letter in the plaintext
    {
        if (islower(plain[i])) // Check if lowercase
        {
            int x = letter_position(plain[i]); // Check letter position
            plain[i] = key[x - 1];             // Replace the plaintext letter by the key
            plain[i] = tolower(plain[i]);
        }
        else if (isupper(plain[i])) // Same for Uppercase
        {
            int x = letter_position(plain[i]);
            plain[i] = key[x - 1];
            plain[i] = toupper(plain[i]);
        }
        else
        {
            plain[i] = plain[i]; // If not letter, do nothing
        }
    }
    printf("ciphertext: %s\n", plain);
    return 0;
}

int letter_position(char text) // get letter position function
{
    int position = 0;

    if (isupper(text)) // if letter is uppercase
    {
        text = tolower(text);
        position = text - 96;
    }
    else // if letter is lowercase
    {
        position = text - 96;
    }
    return position;
}