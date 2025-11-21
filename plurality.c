#include <cs50.h>
#include <stdio.h>
#include <string.h>


#define MAX 9

// Each candidate has a name and a vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Global array that holds all candidates
candidate candidates[MAX];

// How many candidates are actually running
int candidate_count;


bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

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

    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}


// vote:  returns true if the name matches a candidate,
// and increments that candidate's vote count.
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


void print_winner(void)
{
    int max = 0;               // will hold the largest vote count

    // first step - figure out what the max is
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max)
        {
            max = candidates[i].votes;
        }
    }

    // second step - print everyone who reached that max
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max)
        {
            printf("%s\n", candidates[i].name);
        }
    }


    printf("\n");
}
