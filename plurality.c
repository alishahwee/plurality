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
}
candidate;

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
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    string current_winner;
    int current_highest_vote = 0;
    int tied_candidates = 0;
    string tied_winner[MAX - 1]; // Does not include initial winner;
    int tied_highest_vote = 0;

    if (candidate_count < 2) // If just one candidate, they are winner automatically
    {
        current_winner = candidates[0].name;
        current_highest_vote = candidates[0].votes;
    }

    for (int i = 0; i < candidate_count; i++) // If more than one candidate, will calculate highest vote and possible tied votes
    {
        if (candidate_count > 1 && candidates[i].votes > current_highest_vote)
        {
            current_winner = candidates[i].name;
            current_highest_vote = candidates[i].votes;
        }
        else if (candidate_count > 1 && candidates[i].votes == current_highest_vote)
        {
            tied_candidates++;
            tied_winner[i - 1] = candidates[i].name; // Tied winners do not include the initial winner
            tied_highest_vote = candidates[i].votes;
        }
    }
    printf("%s\n", current_winner);

    if (current_highest_vote == tied_highest_vote) // Prints tied winners
    {
        for (int i = 0; i < tied_candidates; i++)
        {
            printf("%s\n", tied_winner[i]);
        }
    }
    return;
}

