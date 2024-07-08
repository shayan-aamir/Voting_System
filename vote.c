#include <stdio.h>
#include <stdlib.h>
#define NUM_CANDIDATES 3
typedef struct {
    char name[50];
    int votes;
} Candidate;
int main() {
    Candidate candidates[NUM_CANDIDATES] = {
        {"Asad", 0},
        {"Shayan", 0},
        {"Burhan", 0}
    };
    printf("Welcome to the Online Voting System!\n");
    while (1) {
        printf("\nCandidates:\n");
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            printf("%d. %s\n", i + 1, candidates[i].name);
        }
        printf("Enter the number of the candidate you want to vote for (0 to exit): ");
        int choice;
        scanf("%d", &choice);
        if (choice < 0 || choice > NUM_CANDIDATES) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
        if (choice == 0) {
            break;
        }
        candidates[choice - 1].votes++;
        printf("You voted for %s. Thank you!\n", candidates[choice - 1].name);
    }
    printf("\nResults:\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }
    return 0;
}