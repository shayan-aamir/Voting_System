#include <stdio.h>
#include <stdlib.h>
#define NUM_CANDIDATES 3
typedef struct {
    char name[50];
    int votes;
} Candidate;
void displayCandidates(Candidate candidates[]) {
    printf("\nCandidates:\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
}
int getVote() {
    int choice;
    printf("Enter the number of the candidate you want to vote for (0 to exit): ");
    scanf("%d", &choice);
    return choice;
}
void processVote(Candidate candidates[], int choice) {
    if (choice < 0 || choice > NUM_CANDIDATES) {
        printf("Invalid choice. Please try again.\n");
        return;
    }
    if (choice != 0) {
        candidates[choice - 1].votes++;
        printf("You voted for %s. Thank you!\n", candidates[choice - 1].name);
    }
}
void displayResults(Candidate candidates[]) {
    printf("\nResults:\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }
}
int main() {
    Candidate *candidates = (Candidate *)malloc(NUM_CANDIDATES * sizeof(Candidate));
    if (candidates == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return 1;
    }
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        sprintf(candidates[i].name, "Candidate %d", i + 1);
        candidates[i].votes = 0;
    }
    printf("\t\t\t\t\t\tWelcome to the Online Voting System!\n");
    while (1) {
        displayCandidates(candidates);
        int choice = getVote();
        if (choice == 0) {
            break;
        }
        processVote(candidates, choice);
    }
    displayResults(candidates);
    free(candidates);
    return 0;
}