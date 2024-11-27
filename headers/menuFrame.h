//Menu and welcome Related Operations
#include<stdio.h>
#include <string.h>
#include <stdlib.h>


void welcome(){
    printf("***************************************************************************\n");
    printf("*********************Welcome To Hotel Management System********************\n");
    printf("***************************************************************************\n");
    printf("Press Any key to continue\n");
    getchar();
}

void clearScreen() {
    system("cls");
}

int role_menu(){
    int role;
    do {
        printf("Main Menu \n");
        printf("0.Administrator \n");
        printf("1.Hotel Staff \n");
        printf("2.Customer \n");
        printf("3.Guest \n");
        printf("4.Exit \n");
        printf("Enter Your Role : ");
        scanf("%d",&role);
        clearScreen();
        if (role < 0 || role > 4)
            printf("Invalid Role. Choose a valid role.\n");
    } while (role < 0 || role > 4);
    return role;
}

int admin_menu(){
    int action;
    do {
        printf("1.Register new users (hotel staff, customers) into the system \n");
	    printf("2.Manage existing users by updating their account status.\n");
	    printf("3.Manage the hotel rooms by adding, updating, or removing room details\n");
        printf("4.Logout\n");
        printf("Please choose an action:-");
        scanf("%d",&action);
        clearScreen();
        if (action < 1 || action > 4) {
            printf("Invalid Input given. Please enter a valid input.\n");
        }
    } while (action < 1 || action > 4);
    return action;
}
int staff_menu(){
    printf("Welcome to Staff Menu.\n");
    return 0;
}

int customer_menu(){
    int action;
    do{
        printf("Welcome to Customer Menu.\n");
	    printf("1.Search for available rooms. \n");
	    printf("2.Make and cancel reservations. \n");
        scanf("%d",&action);
	    printf("3.View reservation history and current bookings. \n");
        if (action < 1 || action > 3) {
                printf("Invalid Input given. Please enter a valid input.\n");
            }
    } while (action < 1 || action > 3);
    
    return action;

}

int guest_menu(){
    printf("Welcome to Guest Menu.\n");
    return 0;
}