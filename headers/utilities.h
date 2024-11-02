//Combining user,rooms and bookings
#include <stdio.h>
#include <string.h>
#include "./user.h"
#include "./menuFrame.h"
#include "./rooms.h"

int freeMemory(){
    free(users); 
    free(rooms);
}

int manageHotelRooms(){
    int choice;
    do{
        printf("1.Update Room Details.\n");
        printf("2.Delete Room Details.\n");
        printf("Choose an Option :- ");
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1:
                updateRoomDetails();
                break;
            case 2:
                deleteRoomDetails();
                break;
            default:
                printf("Invalid Input. Please enter a valid Input.\n");
        }
    }while(choice <0 && choice >2);
}

int admin_functions(int choice){
    clearScreen();
    switch(choice){
        case 1:
            printf("Enter details for new users\n");
            addUser();
            return 1;
            break;
        case 2:
            updateUser();
            return 1;
            break;
        case 3:
            manageHotelRooms();
            break;
            return 1;
        case 4:
            break;
        default:
        return 0;
        break;
    }
    return 0;
}

void role_related_activities(int role){
    int choice;
    switch (role)
    {
        case 0:
            choice =admin_menu();
            getchar();
            admin_functions(choice);
            break;
        case 1:
            choice=staff_menu();
            break;
        case 2:
            choice=customer_menu();
            break;
        default:
            printf("Invalid Input\n");
            break;
    }
}