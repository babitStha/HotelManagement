#include <stdio.h>
#include <string.h>
#include "headers/user.h"
#include "headers/menuFrame.h"


int main()
{
    int choice;
    User loggedInUser;
    welcome();
    clearScreen();
    if (!loadUsers())
        return 1;
    addUser();
    
    int role = role_menu();
    getchar();
    loggedInUser = login(role);
    if(strlen(loggedInUser.username) != 0){
        printf("Hello %s!, You are Logged in As %s.\n",loggedInUser.fullName,loggedInUser.username);
        switch (role)
        {
        case 0:
            admin_menu();
            break;
        case 1:
            staff_menu();
            break;
        case 2:
            customer_menu();
            break;
        default:
            printf("Invalid Input\n");
            break;
        }
        
    }else{
        printf("Login Failed!! Exiting From system");
        return 1;
    }
    
    
    freeMemory();
    return 0;
}