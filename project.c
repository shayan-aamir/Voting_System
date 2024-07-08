#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
void home();
void handler();
int selecting();

#define FILENAME_SIZE 1024

int removeLine(int n, char *filename, char *updated)
{
    FILE *file, *temp;
    // char filename[] = "voters.txt";
    char temp_filename[] = "temp____.txt";
    // strcat(temp_filename, filename);
    char buffer[256]; // Adjust the buffer size as needed

    file = fopen(filename, "r");
    temp = fopen(temp_filename, "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error opening file(s).\n");
        return 1;
    }

    int current_line = 1;
    bool keep_reading = true;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (current_line == n)
        {
            // printf("Reached\n");
            fputs(updated, temp);
        }
        else
        {
            fputs(buffer, temp);
        }

        current_line++;
    }

    fclose(file);
    fclose(temp);

    remove(filename);
    rename(temp_filename, filename);

    return 0;
}

void voting()
{
    system("cls");
    // Implement the voting logic
    printf("Choose your candidate\n");
    FILE *f;
    f = fopen("candidate.txt", "r");

    if (f == NULL)
    {
        printf("File not opened");
        return;
    }
    char buffer[256];
    int i = 1;
    fgets(buffer, sizeof(buffer), f);
    while (fgets(buffer, sizeof(buffer), f) != NULL)
    {
        printf("%d: %s", i, buffer);
        i++;
    }

    int n;
    scanf("%d", &n);
    FILE *polls;
    polls = fopen("polls.txt", "r");
    i = 1;

    if (polls == NULL)
    {
        printf("File not opened");
        return;
    }
    while (fgets(buffer, sizeof(buffer), polls) != NULL && i != n)
    {
        i++;
    }
    int current;
    fscanf(polls, "%d", &current);

    sprintf(buffer, "%d\n", current + 1);
    // printf("%s", buffer);
    removeLine(n, "polls.txt", buffer);
    fclose(polls);
    fclose(f);
    home();
}

int voter()
{
    system("cls");
    char id[8];
    printf("Enter your ID: ");
    scanf("%s", id);

    FILE *fp;
    char buffer[8]; // Assuming the ID is 7 characters + null terminator

    fp = fopen("voters.txt", "r");
    if (fp == NULL)
    {
        printf("File not opened");
        return 0;
    }

    int i = 1;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (buffer[0] == '\n')
            continue;
        // printf("%s %d\n", buffer, i++);
        if (strcmp(buffer, id) == 0)
        {
            fclose(fp);
            removeLine(i, "voters.txt", "voted\n");
            return 1;
        }
        i++;
    }

    printf("Voter not found\n");
    fclose(fp);
    return 0;
}

void polls()
{
    system("cls");
    FILE *p;
    FILE *candidate;
    p = fopen("polls.txt", "r");
    candidate = fopen("candidate.txt", "r");

    if (p == NULL || candidate == NULL)
    {
        printf("File not opened");
        return;
    }

    char buffer[256];
    char bufferName[256];
    fgets(bufferName, sizeof(bufferName), candidate);
    while (fgets(bufferName, sizeof(bufferName), candidate) != NULL && fgets(buffer, sizeof(buffer), p) != NULL)
    {
        bufferName[strlen(bufferName) - 1] = '\0';
        printf("%s: %s", bufferName, buffer);
    }

    fclose(p);
    fclose(candidate);
}

void candidate()
{
    system("cls");
    FILE *fp2;
    fp2 = fopen("polls.txt", "w");
    FILE *fp = fopen("candidate.txt", "w");
    int Cnum, i;
    char buffer[256];
    printf("Enter the number of candidates: ");
    scanf("%d", &Cnum);
    fprintf(fp, "%d\n", Cnum);
    printf("Enter Candidate names:\n");
    for (i = 0; i < Cnum; i++)
    {
        printf("Candidate %d: ", i + 1);
        scanf("%s", buffer);
        fprintf(fp, "%s\n", buffer);
    }
    fclose(fp);
    for (int i = 0; i < Cnum; i++)
    {
        fprintf(fp2, "0\n");
    }
    fclose(fp2);
}

void handler1()
{
    system("cls");
    int choice;
    printf("1. Change Candidate info\n2. View polls\n3. Home\nEnter Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        candidate();
        handler1();
        break;
    /*case 2:
        poll();
        break;*/
    case 3:
        home();
        break;
    }
}

void home()
{
    system("cls");
    int choice = selecting();
    switch (choice)
    {
    case 1:
        handler();
        break;
    case 2:
        if (voter())
        {
            voting();
        }
        else
        {
            printf("Invalid / Voted\n");
            home();
        }
        break;
    }
}

void handler()
{
    system("cls");
    char pass[] = "xyz123"; // password read from 0 pos in candidate file.
    char inPass[10];
    printf("Enter Password: ");
    scanf("%s", inPass);
    if (strcmp(pass, inPass) == 0)
    {
        int choice;
        printf("1. Change candidate info\n2. View polls\n3. Home\nEnter Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            candidate();
            handler1();
            break;
        case 2:
            polls();
            break;
        case 3:
            home();
            break;
        }
    }
    else
    {
        puts("Invalid Password!!!");
        handler();
    }
}

int selecting()
{
    int choice;
    puts("1. Handler\n2. Voter");
    printf("Enter choice: ");
    scanf("%d", &choice);
    if (choice == 1 || choice == 2)
    {
        return choice;
    }
    else
    {
        printf("\nInvalid Choice. Kindly re-enter\n");
        return selecting();
    }
}

int main()
{
    home();
    return 0;
}