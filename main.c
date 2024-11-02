//Main/ Start point of files
#include <stdio.h>
#include <string.h>
#include "headers/utilities.h"

int test() {
    loadRoom(); 
    displayRoom();
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

    
    clearScreen();
    if(strlen(loggedInUser.username) != 0){
        role = role_menu();
        getchar();
        loggedInUser = login(role);
    }
    if(strlen(loggedInUser.username) != 0){
        printf("Hello %s!, You are Logged in As %s.\n",loggedInUser.fullName,loggedInUser.username);
        role_related_activities(role);
    }else{
        printf("Login Failed!! Exiting From system");
        return 1;
    }
    
    
    freeMemory();
    return 0;
}