#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"


void checkAdmin()
{
    if (strcmp(currentUser, ADMIN_USERNAME) != 0)
    {
        printf("Out of reach function call\n\n");
        printf("Quitting the program\n");
        exit(0);
    }
    return;
}

void saveMovies(char movieNames[][50], int movieCount)
{
    FILE *file = fopen("movies.txt", "w");
    if (file == NULL)
    {
        printf("Error saving movies to file.\n");
        return;
    }
    for (int i = 0; i < movieCount; i++)
    {
        fprintf(file, "%s\n", movieNames[i]);
    }
    fclose(file);
}

void adminMenu(char seats[][ROWS][COLS], char movieNames[][50], int movieCount)
{
    checkAdmin();
    int choice;
    while (1)
    {
        printf("\n========== ADMIN MENU ==========\n");
        printf("1. Add Movie\n");
        printf("2. Remove Movie\n");
        printf("3. Show Bookings\n");
        printf("4. Show Users\n");
        printf("5. Show User Bookings\n");
        printf("6. Exit Admin Menu\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            addMovie(movieNames, &movieCount);
        }
        else if (choice == 2)
        {
            removeMovie(movieNames, &movieCount);
        }
        else if (choice == 3)
        {
            showBookings(movieNames, movieCount);
        }
        else if (choice == 4)
        {
            showUsers();
        }
        else if (choice == 5)
        {
            char username[MAX];
            printf("Enter username: ");
            scanf("%s", username);
            showUserBookings(username);
        }
        else if (choice == 6)
        {
            saveMovies(movieNames, movieCount);
            break;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
            return;
        }

    }
}

void addMovie(char movieNames[][50], int *movieCount)
{
    checkAdmin();
    if (*movieCount >= MAX_MOVIES)
    {
        printf("Cannot add more movies.\n");
        return;
    }
    printf("Enter new movie name: ");
    scanf(" %[^\n]", movieNames[*movieCount]);
    FILE *file = fopen("movies.txt", "a");
    if (file == NULL)
    {
        printf("Error opening movies file.\n");
        return;
    }
    fprintf(file, "%s\n", movieNames[*movieCount]);
    fclose(file);
    (*movieCount)++;
}

void removeMovie(char movieNames[][50], int *movieCount)
{
    checkAdmin();
    int movieIndex;
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    showMovies(movieNames, *movieCount);
    printf("Enter the movie number to remove: ");
    scanf("%d", &movieIndex);
    if (movieIndex < 1 || movieIndex > *movieCount)
    {
        printf("Invalid movie selection.\n");
        fclose(tempFile);
        return;
    }
    movieIndex--;
    char movieName[50];
    strcpy(movieName, movieNames[movieIndex]);

    for (int i = 0; i < *movieCount; i++)
    {
        if (i != movieIndex)
        {
            fprintf(tempFile, "%s\n", movieNames[i]);
        }
    }
    fclose(tempFile);
    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    removeBookings(movieName);

    (*movieCount)--;
    printf("Movie removed successfully!\n");
}