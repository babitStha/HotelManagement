//Main/ Start point of files
#include <stdio.h>
#include <string.h>
#include "headers/utilities.h"

int test() {
    loadRoom(); 
    displayRoom("AVAILABLE");
    updateRoomDetails();
    addRoom();
    return 0;
}

void loadData(){
    if (!loadUsers())
        addUser();
    loadRoom(); 
}
int main()
{
    //test();
    //return;
    int choice;
    User loggedInUser;
    int role;
    welcome();
    loadData();
    memset(&loggedInUser, 0, sizeof(loggedInUser)); // set all value to null for loggedInUser

    do{
    clearScreen();
    //Login Part
        if(strlen(loggedInUser.username) == 0){
            role = role_menu();
            if(role == 4){
                printf("Exiting From the system...");
                exit(0);
                return 1;
            }
            getchar();
            if (role == 3){
                //Logging in as a Guest user
                memset(&loggedInUser, 0, sizeof(loggedInUser)); // set all value to null for loggedInUser
                strcpy((loggedInUser.username) , "Guest");
                strcpy((loggedInUser.fullName) , "Guest User");

            }else{
                loggedInUser = login(role);
            }
            
        }
    
    //For action according to role if user is LoggedIn
        if(strlen(loggedInUser.username) != 0){
            printf("Hello %s!, You are Logged in As %s.\n",loggedInUser.fullName,loggedInUser.username);
            role_related_activities(role);
        }else{
            printf("Login Failed!! Exiting From system");
            return 1;
        }
    }while(strlen(loggedInUser.username) != 0);
    
    freeMemory();
    return 0;
}