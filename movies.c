#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_MOVIES 5

// Structure to store movie details
typedef struct {
    char movieName[MAX];
    int availableSeats;
} Movie;

// Structure for User
typedef struct {
    char username[MAX];
    char password[MAX];
} User;

// Function prototypes
void registerUser();
int loginUser();
void logoutUser();
void displayMovies(Movie movies[], int movieCount);
void bookTicket(Movie movies[], int movieCount);
void saveMovies(Movie movies[], int movieCount);
void loadMovies(Movie movies[], int *movieCount);
int checkUserExists(const char *username);

int main() {
    Movie movies[MAX_MOVIES];
    int movieCount = 0;
    int choice;
    int loggedIn = 0;

    loadMovies(movies, &movieCount);

    while (1) {
        if (loggedIn == 0) {
            printf("\n--- Movie Ticket Booking System ---\n");
            printf("1. Register\n");
            printf("2. Login\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    loggedIn = loginUser();
                    if (loggedIn) {
                        printf("Login successful!\n");
                    } else {
                        printf("Login failed!\n");
                    }
                    break;
                case 3:
                    printf("Exiting...\n");
                    exit(0);
                default:
                    printf("Invalid choice, please try again.\n");
            }
        } else {
            printf("\n--- Movie Ticket Booking System ---\n");
            printf("1. View Movies\n");
            printf("2. Book Ticket\n");
            printf("3. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    displayMovies(movies, movieCount);
                    break;
                case 2:
                    bookTicket(movies, movieCount);
                    break;
                case 3:
                    logoutUser();
                    loggedIn = 0;
                    break;
                default:
                    printf("Invalid choice, please try again.\n");
            }
        }
    }

    return 0;
}

void registerUser() {
    FILE *file;
    User user;
    file = fopen("users.txt", "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", user.username);

    if (checkUserExists(user.username)) {
        printf("Username already exists. Try a different one.\n");
        fclose(file);
        return;
    }

    printf("Enter password: ");
    scanf("%s", user.password);

    // Write the username and password to the file
    fprintf(file, "%s %s\n", user.username, user.password);

    printf("User registered successfully!\n");
    fclose(file);
}

int loginUser() {
    FILE *file;
    User user;
    char username[MAX], password[MAX];
    int found = 0;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    file = fopen("users.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    // Read the file to find a matching username and password
    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);
    return found;
}

void logoutUser() {
    printf("Logged out successfully!\n");
}

void displayMovies(Movie movies[], int movieCount) {
    printf("\n--- Available Movies ---\n");
    if (movieCount == 0) {
        printf("No movies available.\n");
        return;
    }
    for (int i = 0; i < movieCount; i++) {
        printf("%d. %s - Available Seats: %d\n", i + 1, movies[i].movieName, movies[i].availableSeats);
    }
}

void bookTicket(Movie movies[], int movieCount) {
    int movieChoice, tickets;
    printf("\n--- Book Ticket ---\n");
    displayMovies(movies, movieCount);

    printf("Enter movie number to book tickets: ");
    scanf("%d", &movieChoice);

    if (movieChoice < 1 || movieChoice > movieCount) {
        printf("Invalid movie number.\n");
        return;
    }

    printf("Enter number of tickets: ");
    scanf("%d", &tickets);

    if (movies[movieChoice - 1].availableSeats < tickets) {
        printf("Not enough seats available.\n");
    } else {
        movies[movieChoice - 1].availableSeats -= tickets;
        printf("Booking successful! You have booked %d tickets for '%s'.\n", tickets, movies[movieChoice - 1].movieName);
    }
}

void saveMovies(Movie movies[], int movieCount) {
    FILE *file = fopen("movies.txt", "w");
    if (file == NULL) {
        printf("Error opening file to save movie data.\n");
        return;
    }

    for (int i = 0; i < movieCount; i++) {
        fprintf(file, "%s %d\n", movies[i].movieName, movies[i].availableSeats);
    }
    fclose(file);
}

void loadMovies(Movie movies[], int *movieCount) {
    FILE *file = fopen("movies.txt", "r");
    if (file == NULL) {
        printf("No movie data found. Adding default movies.\n");

        // Add default movies if the file doesn't exist
        strcpy(movies[0].movieName, "Movie 1");
        movies[0].availableSeats = 100;
        strcpy(movies[1].movieName, "Movie 2");
        movies[1].availableSeats = 150;
        strcpy(movies[2].movieName, "Movie 3");
        movies[2].availableSeats = 80;
        *movieCount = 3;
        return;
    }

    while (fscanf(file, "%s %d", movies[*movieCount].movieName, &movies[*movieCount].availableSeats) != EOF) {
        (*movieCount)++;
    }
    fclose(file);
}

int checkUserExists(const char *username) {
    FILE *file;
    User user;
    file = fopen("users.txt", "r");

    if (file == NULL) {
        return 0;
    }

    while (fscanf(file, "%s %s", user.username, user.password) != EOF) {
        if (strcmp(username, user.username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
