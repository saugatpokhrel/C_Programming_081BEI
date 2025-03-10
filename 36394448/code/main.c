#include <stdio.h>
#include <string.h>
#include "defs.h"
int loadMovies(char movieNames[MAX_MOVIES][50]);
int main()
{
    char seats[MAX_MOVIES][ROWS][COLS];
    char movieNames[MAX_MOVIES][50];
    int movieCount = loadMovies(movieNames);
}


int loadMovies(char movieNames[][50])
{
    FILE *file = fopen("movies.txt", "r");
    int count = 0;
    if (file == NULL)
    {
        // Use default movies if file not found
        strcpy(movieNames[0], "The Shawshank Redemption");
        strcpy(movieNames[1], "Inception");
        strcpy(movieNames[2], "Interstellar");
        count = 3;
        saveMovies(movieNames, count);
        return count;
    }
    while (fgets(movieNames[count], 50, file) != NULL && count < MAX_MOVIES)
    {
        movieNames[count][strcspn(movieNames[count], "\n")] = '\0';
        count++;
    }
    fclose(file);
    return count;
}