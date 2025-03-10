#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
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