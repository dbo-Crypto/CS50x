#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
void compute_winner(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    compute_winner(score1, score2);
}

// Function to compute players scores
int compute_score(string word)
{
    // Change all letters in lower case to count points
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i]))
        {
            if (islower(word[i]))
            {
                word[i] = word[i];
            }
            else
            {
                word[i] = word[i] + 32;
            }
        }
        else
        {
            word[i] = word[i];
        }
        //printf("Formatted word : %s\n", word);
    }
    // TODO: Compute and return score for string
    int count = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i]))
        {
            //printf("%c is a letter\n", word[i]);
            char letter = word[i];
            int position = letter - 'a' + 1;
            //printf("the letter is : %c and the position is %i\n", letter, position);
            int points = POINTS[position - 1];
            //printf("Letter %c os worth %i points\n", letter, points);
            //printf("\n");
            count = count + points;
        }
        else
        {
            count = count + 0;
        }
    }
    //printf("this player has %i points\n", count);
    return count;
}

// Function to give the fianl winner
void compute_winner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    printf("\n");
}
