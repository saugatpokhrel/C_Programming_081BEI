#ifndef DEFS_H
#define DEFS_H
#define MAX 50
#define ROWS 10
#define COLS 10
#define MAX_MOVIES 10
typedef struct
{
    char username[MAX];
    char password[MAX];
} User;
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin"

// Globals
extern int loginStatus;
extern char currentUser[MAX];

//Functions
extern void initializeSeats(char seats[ROWS][COLS]);
extern void updateSeatsFromBookings(char seats[ROWS][COLS], char movieName[]);
extern void showSeats(char seats[ROWS][COLS], char movieName[]);
extern void writeBookingToFile(char *username, char *movieName, char *seats);

#endif