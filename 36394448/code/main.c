#include <stdio.h>
#include <string.h>
#include "defs.h"

void printTicket(char movieName[], int row, int col);
void userBookSeat(char seats[ROWS][COLS], char movieName[]);

void userMenu(char seats[][ROWS][COLS], char movieNames[][50], int movieCount)
{
    if (loginStatus == 0)
    {
        printf("\nERROR: You must log in before booking a seat!\n");
        return;
    }

    int movieIndex;
    showMovies(movieNames, movieCount);
    printf("Enter the movie number you want to book a seat for: ");
    scanf("%d", &movieIndex);
    if (movieIndex < 1 || movieIndex > movieCount)
    {
        printf("Invalid movie selection.\n");
        return;
    }
    movieIndex--;
    userBookSeat(seats[movieIndex], movieNames[movieIndex]);
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
void printTicket(char movieName[], int row, int col)
{
    printf("\n\n====================================\n");
    printf("        MOVIE TICKET     \n");
    printf("------------------------------------\n");
    printf(" Movie: %s\n", movieName);
    printf(" Seat: Row %d, Column %d\n", row + 1, col + 1);
    printf(" Enjoy your movie!  \n");
    printf("====================================\n\n");
}

void userBookSeat(char seats[ROWS][COLS], char movieName[])
{
    if (loginStatus == 0)
    {
        printf("\nERROR: You must log in before booking a seat!\n");
        return;
    }

    int row, col;
    showSeats(seats, movieName);
    while (1)
    {
        printf("Enter row and column number to book a seat (1-%d): ", ROWS);
        scanf("%d %d", &row, &col);

        if (row < 1 || row > ROWS || col < 1 || col > COLS)
        {
            printf("Invalid seat selection. Please choose a seat within range.\n");
            continue;
        }
        row--; // convert to zero-based index
        col--;

        if (seats[row][col] == 'X')
        {
            printf("Seat is already booked. Please choose another seat.\n");
        }
        else
        {
            seats[row][col] = 'X';
            // Save the booking persistently under the current user's name
            writeBookingToFile(currentUser, movieName, row, col);
            printf("Seat booked successfully!\n");
            showSeats(seats, movieName);
            printTicket(movieName, row, col);
            break;
        }
    }
}

void showMovies(char movieNames[][50], int movieCount)
{
    FILE *file = fopen("movies.txt", "r");
    int count = 0;
    printf("Movies available:\n");
    if (file == NULL)
    {
        strcpy(movieNames[0], "The Shawshank Redemption");
        strcpy(movieNames[1], "Inception");
        strcpy(movieNames[2], "Interstellar");
        count = 3;
        saveMovies(movieNames, count);
    }
    while (fgets(movieNames[MAX], 50, file) != NULL && count < MAX_MOVIES)
    {
        printf("%d. %s\n", count + 1, movieNames[count]);
        count++;
    }
    fclose(file);
}
void registerUser()
{
    FILE *file;
    User user;
    file = fopen("users.txt", "a");

    if (file == NULL)
    {
        printf("Error opening users file.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", user.username);

    printf("Enter password: ");
    scanf("%s", user.password);

    fprintf(file, "%s %s\n", user.username, user.password);
    printf("User registered successfully!\n");
    fclose(file);
}

int loginUser()
{
    FILE *file;
    User user;
    char username[MAX], password[MAX];
    int found = 0;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0)
    {
        loginStatus = 1;
        strcpy(currentUser, username);
        printf("Admin login successful! Welcome, %s.\n", username);
        return 2;
    }

    file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening users file.\n");
        return 0;
    }

    while (fscanf(file, "%s %s", user.username, user.password) == 2)
    {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found)
    {
        printf("Login successful! Welcome, %s.\n", username);
        loginStatus = 1;
        strcpy(currentUser, username);
        return 1; // Regular user login
    }
    else
    {
        printf("Invalid username or password.\n");
        return 0;
    }
}

void logoutUser()
{
    if (loginStatus == 1)
    {
        loginStatus = 0;
        currentUser[0] = '\0';
        printf("Logged out successfully!\n");
    }
    else
    {
        printf("You are not logged in.\n");
    }
}

int main()
{
    char seats[MAX_MOVIES][ROWS][COLS];
    char movieNames[MAX_MOVIES][50];
    int movieCount = loadMovies(movieNames);

    for (int i = 0; i < movieCount; i++)
    {
        initializeSeats(seats[i]);
        updateSeatsFromBookings(seats[i], movieNames[i]);
    }

    int choice;
    while (1)
    {
        printf("\n========== MOVIE BOOKING SYSTEM ==========\n");
        printf("1. Book a Seat \n");
        printf("2. Register\n");
        printf("3. Login\n");
        printf("4. Logout\n");
        printf("5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (loginStatus == 0)
            {
                printf("\nERROR: You must log in before booking a seat!\n");
            }
            else
            {
                userMenu(seats, movieNames, movieCount);
            }
        }
        else if (choice == 2)
        {
            registerUser();
        }
        else if (choice == 3)
        {
            int loginResult = loginUser();
            if (loginResult == 2)
            {
                // Admin login: open the admin menu
                adminMenu(seats, movieNames, movieCount);
            }
        }
        else if (choice == 4)
        {
            logoutUser();
        }
        else if (choice == 5)
        {
            printf("Thank you for using the Movie Booking System! \n");
            break;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
