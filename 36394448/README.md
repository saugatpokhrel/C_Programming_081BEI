# Theater Management System

## Overview

The **Theater Management System** is a console-based application written in **C** that allows admins to manage movies, add movies,remove movies and see sales information. Customers can search for movies and book seats for a movie accordingly.

## Features

### Admin Panel

- **Admin Login**: Secure access to admin functionalities using the following credentials:
  - **Username**: admin  
  - **Password**: admin  
- **Add movie**: Add new movies to the movies list.
- **Remove Bookings**: Admin can remove the movies from the list.
- **View Bookings**: View booking for all the movies along with bookings made by an user.


### User Panel

- **Create account**: Users can create account which helps them to book movie and store data about the movies booked.
- **Search Movies**: Users can search for movies
- **Select Seats**: Users can select seats for  movies they want to see



## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/C_Programming_081BEI.git
   ```
2. Navigate to the project branch:
   ```bash
   cd 36394448
   ```
3. Navigate to code dictionary:
   ```bash
   cd code
   ```
3. Compile the C program:
   ```bash
    gcc main.c init.c admin.c -o main

   ```
4. Run the executable:
   ```bash
   ./main
   ```

## Usage

1. Run the application and choose between **Admin** and **User** modes.
2. If you are an **admin**, enter the login credentials (**Username: admin, Password: admin**) and perform  management tasks.
3. If you are a **User**, search for movies,select seats and get your ticket
4. Exit the program after completing your session.

## Code Structure

- `main.c`: Main source file containing all functionalities.
- `admin.c`: Handles admin-related operations.
- `init.c`: Manages initial inits.
- `defs.h`: Stores global variables and functions.
- `bookings.txt`: Stores  bookings data.
- `users.txt`: Stores  user data.
- `movies.txt`: Stores  movies data.
- `Makefile`: Stores  compilation instructions.

## Future Enhancements

- Implement **User Login** with additional functionalities such as bookings  history.
- Add a **Graphical User Interface (GUI)** for better user experience.
- Add a **Movies Scheduling System** for better user experience and theater management.
- Introduce a **database system (MySQL or SQLite)** for persistent storage.
- Implement **movies recommendations** based on customer preferences.
- Enhance **security measures** for login credentials.