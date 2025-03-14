#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

// Assumes currentUser and ADMIN_USERNAME are defined in defs.h

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

void removeBookings(char movieName[])
{
    checkAdmin();
    FILE *bookingsFile = fopen("bookings.txt", "r");
    if (bookingsFile == NULL)
    {
        // If there is no bookings file, there is nothing to remove.
        return;
    }
    FILE *tempBookings = fopen("temp_bookings.txt", "w");
    if (tempBookings == NULL)
    {
        fclose(bookingsFile);
        printf("Error creating temporary bookings file.\n");
        return;
    }
    char line[256];
    char bookedUser[MAX];
    char bookedMovie[50];
    int row, col;
    while (fgets(line, sizeof(line), bookingsFile))
    {
        // Parse the line; expected format: username|movieName|row|col
        if (sscanf(line, "%[^|]|%[^|]|%d|%d", bookedUser, bookedMovie, &row, &col) == 4)
        {
            // Write the line only if it doesn't match the movie to be removed
            if (strcmp(bookedMovie, movieName) != 0)
            {
                fputs(line, tempBookings);
            }
        }
        else
        {
            // In case of an unexpected format, copy the line over.
            fputs(line, tempBookings);
        }
    }
    fclose(bookingsFile);
    fclose(tempBookings);
    remove("bookings.txt");
    rename("temp_bookings.txt", "bookings.txt");
}

void showBookings(char movieNames[][50], int movieCount)
{
    checkAdmin();
    for (int i = 0; i < movieCount; i++)
    {
        showBookingsForMovie(movieNames[i]);
    }
}

void showBookingsForMovie(char movieName[])
{
    checkAdmin();
    FILE *file = fopen("bookings.txt", "r");
    if (file == NULL)
    {
        return;
    }
    char bookedUser[MAX];
    char bookedMovie[50];
    int row, col;
    int count = 0;
    printf("\nBookings for \"%s\":\n", movieName);
    while (fscanf(file, "%[^|]|%[^|]|%d|%d\n", bookedUser, bookedMovie, &row, &col) == 4)
    {
        if (strcmp(bookedMovie, movieName) == 0)
        {
            printf("%d. %s - Row %d, Col %d\n", ++count, bookedUser, row + 1, col + 1);
        }
    }
    fclose(file);
}

void showUsers()
{
    checkAdmin();
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        return;
    }
    User user;
    printf("\nRegistered Users:\n");
    while (fscanf(file, "%s %s", user.username, user.password) == 2)
    {
        printf("%s\n", user.username);
    }
    fclose(file);
}

void showUserBookings(char username[])
{
    checkAdmin();
    FILE *file = fopen("bookings.txt", "r");
    if (file == NULL)
    {
        return;
    }
    char bookedUser[MAX];
    char bookedMovie[50];
    int row, col;
    int count = 0;
    printf("\nBookings for \"%s\":\n", username);
    while (fscanf(file, "%[^|]|%[^|]|%d|%d\n", bookedUser, bookedMovie, &row, &col) == 4)
    {
        if (strcmp(bookedUser, username) == 0)
        {
            printf("%d. %s - Row %d, Col %d\n", ++count, bookedMovie, row + 1, col + 1);
        }
    }
    fclose(file);
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