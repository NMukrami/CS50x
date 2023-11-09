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
    // loop
    for (int n = 0; n < candidate_count; n++)
    {
        // check if name matches any of name in array
        if (strcmp(candidates[n].name, name) == 0)
        {
            // update vote by 1
            candidates[n].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest_votes_candidate = 0;

    // loop
    for (int v = 0; v < candidate_count; v++)
    {
        // if high than highest votes assign it
        if (candidates[v].votes > highest_votes_candidate)
        {
            highest_votes_candidate = candidates[v].votes;
        }
    }
    // loop
    for (int v = 0; v < candidate_count; v++)
    {
        // if equal to than print candidate name with highest votes
        if (highest_votes_candidate == candidates[v].votes)
        {
            printf("%s\n", candidates[v].name);
        }
    }
    return;
}