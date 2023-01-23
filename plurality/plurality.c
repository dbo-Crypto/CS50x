#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            // printf("%s got a vote, %s has %i votes\n",candidates[i].name, candidates[i].name, candidates[i].votes);
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    string temp_name;
    int temp_votes;
    for (int j = 0; j < candidate_count - 1; j++)
    {
        for (int i = 0; i <= candidate_count - 2; i++)
        {
            if (candidates[i].votes < candidates[i + 1].votes) // Reverse sorting program from higher to lower votes number
            {
                temp_votes = candidates[i].votes;
                temp_name = candidates[i].name;
                candidates[i].votes = candidates[i + 1].votes;
                candidates[i].name = candidates[i + 1].name;
                candidates[i + 1].name = temp_name;
                candidates[i + 1].votes = temp_votes;
            }
        }
    }
    int counter = 0;
    for (int k = 0; k <= candidate_count - 2; k++) // Program to determine which name(s) to return in case of tie.
    {
        if (candidates[k].votes == candidates[k + 1].votes)
        {
            counter++;
        }
    }
    if (candidates[0].votes == candidates[1].votes)
    {
        for (int l = 0; l <= counter; l++)
        {
            printf("%s\n", candidates[l].name);
        }
    }
    else
    {
        printf("%s\n", candidates[0].name);
    }
    return;
}