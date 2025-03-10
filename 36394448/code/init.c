#include<stdio.h>
#include<string.h>
#include "defs.h"
int loginStatus = 0;
char currentUser[MAX]={0};
void initializeSeats(char seats[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            seats[i][j] = 'O';
        }
    }
}
void updateSeatsFromBookings(char seats[ROWS][COLS], char movieName[])
{
    FILE *file = fopen("bookings.txt", "r");
    if (file == NULL)
    {
        return;
    }

    char bookedUser[MAX];
    char bookedMovie[50];
    int row, col;

    while (fscanf(file, "%[^|]|%[^|]|%d|%d\n", bookedUser, bookedMovie, &row, &col) == 4)
    {
        if (strcmp(bookedMovie, movieName) == 0)
        {
            if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
            {
                seats[row][col] = 'X';
            }
        }
    }
    fclose(file);
}

void showSeats(char seats[ROWS][COLS], char movieName[])
{
    updateSeatsFromBookings(seats, movieName);
    
    printf("\n\n=============== Seat Layout for %s ===============\n", movieName);
    printf("    ");
    for (int j = 0; j < COLS; j++)
    {
        printf(" %2d ", j + 1);
    }
    printf("\n-----------------------------------------------------\n");
    for (int i = 0; i < ROWS; i++)
    {
        printf("Row %2d |", i + 1);
        for (int j = 0; j < COLS; j++)
        {
            printf("[%c] ", seats[i][j]);
        }
        printf(" |\n");
    }
    printf("-----------------------------------------------------\n");
}
void writeBookingToFile(char *username, char *movieName, int row, int col)
{
    FILE *file = fopen("bookings.txt", "a");
    if (file == NULL)
    {
        printf("Error opening bookings file.\n");
        return;
    }
    fprintf(file, "%s|%s|%d|%d\n", username, movieName, row, col);
    fclose(file);
}