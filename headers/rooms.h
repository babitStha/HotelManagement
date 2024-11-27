//For Rooms Related Operations
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROOMFILE_PATH "data/rooms.txt"
#define INITIAL_MAX_ROOM 20

typedef struct ROOM {
    char room_number[10];
    float price;
    int isAvailable; // 0 = NA, 1 = A
    int capacity;
    int isBathroomAttached;
    int hasBalcony;
} ROOM;

ROOM *rooms = NULL;
int maxRoom = INITIAL_MAX_ROOM;
int roomcount = 0;

int loadRoom() {
    FILE *file = fopen(ROOMFILE_PATH, "rb");
    if (file == NULL) {
        // File doesn't exist; create it
        file = fopen(ROOMFILE_PATH, "wb");
        if (file == NULL) {
            perror("Could not create room details file");
            return 0;
        }
        fclose(file);
        printf("Room details file created. You can add rooms now.\n");
        return 1; 
    }

    rooms = (ROOM *)malloc(maxRoom * sizeof(ROOM));
    if (rooms == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 0;
    }

    roomcount = 0;
    while (roomcount < maxRoom && fread(&rooms[roomcount], sizeof(ROOM), 1, file) == 1) {
        roomcount++;
    }
    fclose(file);
    return 1;
}

int saveRoom() {
    FILE *file = fopen(ROOMFILE_PATH, "wb");
    if (file == NULL) {
        perror("Could not open file to write. Creating new file.");
        return 0; 
    }

    fwrite(rooms, sizeof(ROOM), roomcount, file);
    fclose(file);
    return 1; 
}

int checkRoomExists(const char *room_number) {
    for (int i = 0; i < roomcount; i++) {
        if (strcmp(rooms[i].room_number, room_number) == 0) {
            return 1; 
        }
    }
    return 0;
}

void addRoom() {
    if (rooms == NULL) {
        rooms = (ROOM *)malloc(maxRoom * sizeof(ROOM));
        if (rooms == NULL) {
            perror("Memory allocation failed");
            return;
        }
    }
    ROOM room;
    printf("Enter Room ID: ");
    fgets(room.room_number, sizeof(room.room_number), stdin);
    room.room_number[strcspn(room.room_number, "\n")] = 0; 

    if (checkRoomExists(room.room_number)) {
        printf("Room %s already exists.\n", room.room_number);
        return;
    }

    printf("Enter Price for room %s: ", room.room_number);
    scanf("%f", &room.price);

    printf("Enter Capacity of People for room %s: ", room.room_number);
    scanf("%d", &room.capacity);
    room.isAvailable = 1;

    do {
        printf("Is bathroom attached in room %s? (0 = NO, 1 = YES): ", room.room_number);
        scanf("%d", &room.isBathroomAttached);
    } while (room.isBathroomAttached < 0 || room.isBathroomAttached > 1);

    do {
        printf("Does room %s have a balcony? (0 = NO, 1 = YES): ", room.room_number);
        scanf("%d", &room.hasBalcony);
    } while (room.hasBalcony < 0 || room.hasBalcony > 1);

    if (roomcount >= maxRoom) {
        maxRoom *= 2;
        rooms = (ROOM*)realloc(rooms, maxRoom * sizeof(ROOM));
        if (rooms == NULL) {
            perror("Memory reallocation failed");
            return;
        }
    }

    rooms[roomcount++] = room; 

    if (!saveRoom()) {
        printf("Failed to save room data.\n");
        return; 
    }
    
    printf("Room %s added successfully.\n", room.room_number);
}

void displayRoom(char filter[10]) {
    int displayedRoom =0 ;
    if (roomcount == 0) {
        printf("No rooms available to display.\n");
        return;
    }

    for (int i = 0; i < roomcount; i++) {
        if (filter != NULL){
            if(strcmp(filter, "AVAILABLE") == 0){
                if(!rooms[i].isAvailable){
                    continue; // skip print if room is not available
                }
            }
            else{ //Display by room number if not NULL /AVAILABLE
                if(strcmp(rooms[i].room_number , filter)!=0)
                    continue;
                }
        }

        if (i == 0) {
            printf("**********************************************\n");
        }
        printf("Room Number: %s details\n", rooms[i].room_number);
        printf("**********************************************\n");
        printf("Room Price: Rs %.2f\n", rooms[i].price);
        printf("Room Capacity: %d person(s)\n", rooms[i].capacity);
        printf("Room Available: %s\n", (rooms[i].isAvailable == 1) ? "Yes" : "No");
        printf("Have Attached Bathroom: %s\n", (rooms[i].isBathroomAttached == 1) ? "Yes" : "No");
        printf("Have Balcony: %s\n", (rooms[i].hasBalcony == 1) ? "Yes" : "No");
        printf("**********************************************\n\n");
        displayedRoom ++;
    }
    if(!displayedRoom){
        printf("Rooms Not available.\n");
    }
    printf("Press any key to continue...\n");
    getchar(); 
}

void updateRoomDetails() {
    ROOM room;
    int found =0;
    printf("Enter Room ID to update: ");
    fgets(room.room_number, sizeof(room.room_number), stdin);
    room.room_number[strcspn(room.room_number, "\n")] = 0; 
        for (int i = 0; i < roomcount; i++) {
            if (strcmp(rooms[i].room_number, room.room_number) == 0) {
                found =1;
                printf("Enter Price for room %s: ", room.room_number);
                scanf("%f", &room.price);

                printf("Enter Capacity of People for room %s: ", room.room_number);
                scanf("%d", &room.capacity);
                room.isAvailable = 1;

                do {
                    printf("Is bathroom attached in room %s? (0 = NO, 1 = YES): ", room.room_number);
                    scanf("%d", &room.isBathroomAttached);
                } while (room.isBathroomAttached < 0 || room.isBathroomAttached > 1);

                do {
                    printf("Does room %s have a balcony? (0 = NO, 1 = YES): ", room.room_number);
                    scanf("%d", &room.hasBalcony);
                } while (room.hasBalcony < 0 || room.hasBalcony > 1); 
                rooms[i] = room; 
                if (!saveRoom()) {
                    printf("Failed to save room data.\n");
                    return; 
                }
 
            }
    }
    if(found){
        printf("Room %s Updated successfully.\n", room.room_number);
    }else{
        printf("Room %s doesnt exists.\n", room.room_number);
    }
    printf("Press any key to continue.");
    getchar();
    
}

void deleteRoomDetails() {
    if (roomcount == 0) {
        printf("No rooms available to delete.\n");
        return;
    }

    char room_number[10];
    int found = 0;

    printf("Enter Room ID to Delete: ");
    fgets(room_number, sizeof(room_number), stdin);
    room_number[strcspn(room_number, "\n")] = 0;

    for (int i = 0; i < roomcount; i++) {
        if (strcmp(rooms[i].room_number, room_number) == 0) {
            found = 1;
            printf("Deleting Room %s...\n", room_number);
            for (int j = i; j < roomcount - 1; j++) {
                rooms[j] = rooms[j + 1]; 
            }
            roomcount--; 

            break;
        }
    }

    if (!found) {
        printf("Room ID %s not found.\n", room_number);
        return;
    }
    if (!saveRoom()) {
        printf("Failed to save updated room data.\n");
        return; 
    }
    printf("Room %s deleted successfully.\n", room_number);
}
