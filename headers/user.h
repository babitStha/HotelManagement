#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERFILE_PATH "data/users/user.txt"
#define INITIAL_MAX_USERS 20

typedef struct User {
    char username[50];
    char password[50];
    char status;
    char fullName[100];
    char address[50];
    char contact[50];
    int role;
} User;

User *users = NULL;
int userCount = 0;
int maxUsers = INITIAL_MAX_USERS;

int loadUsers() {
    FILE *file = fopen(USERFILE_PATH, "rb");
    if (file == NULL) {
        perror("User not found for system. Please create");
        return 0;
    }

    users = (User *)malloc(maxUsers * sizeof(User));
    if (users == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 0;
    }

    userCount = 0;
    while (userCount < maxUsers && fread(&users[userCount], sizeof(User), 1, file) == 1) {
        userCount++;
        if (userCount >= maxUsers) {
            maxUsers *= 2;
            users = (User *)realloc(users, maxUsers * sizeof(User));
            if (users == NULL) {
                perror("Memory reallocation failed");
                fclose(file);
                return 0;
            }
        }
    }
    fclose(file);
    return 1;
}

int saveUsers() {
    FILE *file = fopen(USERFILE_PATH, "wb");
    if (file == NULL) {
        perror("Could not open file to write");
        return 0; 
    }

    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
    return 1; 
}

int checkUserExists(const char *username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1; // Username exists
        }
    }
    return 0; // Username does not exist
}

void addUser() {
        if (users == NULL) {
             users = (User *)  malloc(maxUsers * sizeof(User));
             if (users == NULL) {
                return;
             }
        }
    User user;
    printf("Enter Username: ");
    fgets(user.username, sizeof(user.username), stdin);
    user.username[strcspn(user.username, "\n")] = 0;

    if (checkUserExists(user.username)) {
        printf("User %s already exists.\n", user.username);
        return;
    }

    printf("Enter Password: ");
    fgets(user.password, sizeof(user.password), stdin);
    user.password[strcspn(user.password, "\n")] = 0;

    do {
        printf("0. Admin\n1. Hotel Staff\n2. Customer\nChoose a Role: ");
        scanf("%d", &user.role);
        getchar(); // Clear newline
        if (user.role < 0 || user.role > 2) {
            printf("Invalid role selected. Please enter a valid role.\n");
        }
    } while (user.role < 0 || user.role > 2);


    printf("Enter User's Full Name: ");
    fgets(user.fullName, sizeof(user.fullName), stdin);
    user.fullName[strcspn(user.fullName, "\n")] = 0;

    printf("Enter User's Address: ");
    fgets(user.address, sizeof(user.address), stdin);
    user.address[strcspn(user.address, "\n")] = 0;

    printf("Enter User's Contact: ");
    fgets(user.contact, sizeof(user.contact), stdin);
    user.contact[strcspn(user.contact, "\n")] = 0;
    printf("%s",user.contact);

    user.status = 'A'; // Active

    users[userCount++] = user;
    printf("%s",user.contact);

    if (userCount >= maxUsers) {
        maxUsers *= 2;
        users = (User *)realloc(users, maxUsers * sizeof(User));
        if (users == NULL) {
            perror("Memory reallocation failed");
            return;
        }
    }

    if (!saveUsers())
        return; 
    printf("User %s added successfully.\n", user.username);
}

void deleteUser() {
    char username[50];
    int found = 0;

    printf("Enter Username to Delete: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            found = 1;
            printf("Deleting user %s.\n", username);
            for (int j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1]; 
            }
            userCount--; 
            break;
        }
    }

    if (!found) {
        printf("User %s not found.\n", username);
        return;
    }

    if (!saveUsers())
        return; 
    printf("User deleted successfully.\n");
}

void updateUser() {
    char username[50];
    int found = 0;

    printf("Enter Username to Update: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            found = 1;
            printf("Updating user %s.\n", username);
            printf("Enter New Password: ");
            fgets(users[i].password, sizeof(users[i].password), stdin);
            users[i].password[strcspn(users[i].password, "\n")] = 0;

            printf("Enter User's Full Name: ");
            fgets(users[i].fullName, sizeof(users[i].fullName), stdin);
            users[i].fullName[strcspn(users[i].fullName, "\n")] = 0;

            printf("Enter User's Address: ");
            fgets(users[i].address, sizeof(users[i].address), stdin);
            users[i].address[strcspn(users[i].address, "\n")] = 0;

            printf("Enter User's Contact: ");
            fgets(users[i].contact, sizeof(users[i].contact), stdin);
            users[i].contact[strcspn(users[i].contact, "\n")] = 0;
            break;
        }
    }

    if (!found) {
        printf("User %s not found.\n", username);
        return;
    }

    if (!saveUsers())
        return; 
    printf("User updated successfully.\n");
}

void freeMemory() {
    free(users); 
}
User login(int role) {
    User loggedInUser;
    memset(&loggedInUser, 0, sizeof(User));  // Initialize to zeros
    char enteredUsername[50];
    char enteredPassword[50];
    int attempt = 3;

    while (attempt > 0) {
        printf("You have %d attempts left.\n", attempt);
        printf("Enter Username: ");
        fgets(enteredUsername, sizeof(enteredUsername), stdin);
        enteredUsername[strcspn(enteredUsername, "\n")] = 0;

        printf("Enter Password: ");
        fgets(enteredPassword, sizeof(enteredPassword), stdin);
        enteredPassword[strcspn(enteredPassword, "\n")] = 0;

        for (int j = 0; j < userCount; j++) {
            // Check username, password, and role
            if (strcmp(users[j].username, enteredUsername) == 0 &&
                strcmp(users[j].password, enteredPassword) == 0 &&
                users[j].role == role) {
                loggedInUser = users[j];
                printf("Login successful! Welcome, %s.\n", loggedInUser.fullName);
                return loggedInUser; // Return the logged-in user
            }
        }

        attempt--;
        printf("Invalid username or password!%s\n", attempt > 0 ? " Try again." : "");
    }

    printf("Too many failed attempts. Please try again later.\n");
    return loggedInUser; // Returns an empty user if login fails
}
