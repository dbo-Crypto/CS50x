#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Prototype declarations
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
float index_calculation(int nb_letters, int nb_words, int nb_sentences);

int main(void)
{
    string text = get_string("Text: ");
    int nb_letters = count_letters(text);
    int nb_words = count_words(text);
    int nb_sentences = count_sentences(text);
    index_calculation(nb_letters, nb_words, nb_sentences);
}


// Function to count letters
int count_letters(string text)
{
    int count;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count = count + 1 ;
            //printf("%i letters", count);
        }
        else
        {
            count = count + 0;
        }
    }
    //printf("%i letters", count);
    //printf("\n");
    return count;
}


// Function to count words
int count_words(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //printf("Letter analyzed is: %c\n", text[i]);
        if (isspace(text[i]) && text[-1] != text[1])
        {
            count = count + 1;
            //printf("Counter: %i\n",count);
        }
        else if (text[i + 1] == '\0')
        {
            count = count + 1;
        }
        else
        {
            count = count + 0;
        }
    }
    //printf("%i words", count);
    //printf("\n");
    return count;
}

// Function to count sentences
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //printf("Letter analyzed is: %c\n", text[i]);
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count = count + 1;
            //printf("Counter: %i\n",count);
        }
        else
        {
            count = count + 0;
        }
    }
    //printf("%i sentences", count);
    //printf("\n");
    return count;
}

float index_calculation(int nb_letters, int nb_words, int nb_sentences)
{
    float L = 0;
    L = (float)nb_letters / (float)nb_words * 100.0;
    //printf("L is: %f\n", L);

    float S = 0;
    S = (float)nb_sentences / (float)nb_words * 100.0;
    //printf("S is: %f\n", S);

    float index = 0;
    index = (0.0588 * L - 0.296 * S - 15.8);
    //printf("Index: %f\n", index);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        index = round(index);
        printf("Grade %i\n", (int)index);
    }
    return index;

}