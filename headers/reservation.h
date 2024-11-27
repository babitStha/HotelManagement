#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#define BOOKING_FILE_PATH "data/bookings.txt"
#define INITIAL_LOAD 20

typedef struct BOOKING {
    char roomNumber[10];
    char checkinDate[10];
    char checkOutDate[10];
    char status[10];
    char bookedBy[50];
} BOOKING;


BOOKING *bookings = NULL;
int maxBooking = INITIAL_LOAD;
int bookingcount = 0;

int loadBookings() {
    FILE *file = fopen(BOOKING_FILE_PATH, "rb");
    if (file == NULL) {
        // File doesn't exist; create it
        file = fopen(BOOKING_FILE_PATH, "wb");
        if (file == NULL) {
            perror("Could not create BOOKING details file");
            return 0;
        }
        fclose(file);
        return 1; 
    }

    bookings = (BOOKING *)malloc(maxBooking * sizeof(BOOKING));
    if (bookings == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 0;
    }

    bookingcount = 0;
    while (bookingcount < maxBooking && fread(&bookings[bookingcount], sizeof(BOOKING), 1, file) == 1) {
        bookingcount++;
    }
    fclose(file);
    return 1;
}

int saveBOOKING() {
    FILE *file = fopen(BOOKING_FILE_PATH, "wb");
    if (file == NULL) {
        perror("Could not open file to write. Creating new file.");
        return 0; 
    }

    fwrite(bookings, sizeof(BOOKING), bookingcount, file);
    fclose(file);
    return 1; 
}

int checkBOOKINGExists(const char *roomNumber) {
    for (int i = 0; i < bookingcount; i++) {
        if (strcmp(bookings[i].roomNumber, roomNumber) == 0) {
            return 1; 
        }
    }
    return 0;
}

void addBOOKING() {
    if (bookings == NULL) {
        bookings = (BOOKING *)malloc(maxBooking * sizeof(BOOKING));
        if (bookings == NULL) {
            perror("Memory allocation failed");
            return;
        }
    }
    BOOKING BOOKING;
    printf("Enter BOOKING ID: ");
    fgets(BOOKING.roomNumber, sizeof(BOOKING.roomNumber), stdin);
    BOOKING.roomNumber[strcspn(BOOKING.roomNumber, "\n")] = 0; 

    if (checkBOOKINGExists(BOOKING.roomNumber)) {
        printf("BOOKING %s already exists.\n", BOOKING.roomNumber);
        return;
    }

    printf("Enter Price for BOOKING %s: ", BOOKING.roomNumber);
    scanf("%f", &BOOKING.price);

    printf("Enter Capacity of People for BOOKING %s: ", BOOKING.roomNumber);
    scanf("%d", &BOOKING.capacity);
    BOOKING.isAvailable = 1;

    do {
        printf("Is bathBOOKING attached in BOOKING %s? (0 = NO, 1 = YES): ", BOOKING.roomNumber);
        scanf("%d", &BOOKING.isBathBOOKINGAttached);
    } while (BOOKING.isBathBOOKINGAttached < 0 || BOOKING.isBathBOOKINGAttached > 1);

    do {
        printf("Does BOOKING %s have a balcony? (0 = NO, 1 = YES): ", BOOKING.roomNumber);
        scanf("%d", &BOOKING.hasBalcony);
    } while (BOOKING.hasBalcony < 0 || BOOKING.hasBalcony > 1);

    if (bookingcount >= maxBooking) {
        maxBooking *= 2;
        BOOKINGs = (BOOKING*)realloc(BOOKINGs, maxBooking * sizeof(BOOKING));
        if (BOOKINGs == NULL) {
            perror("Memory reallocation failed");
            return;
        }
    }

    BOOKINGs[bookingcount++] = BOOKING; 

    if (!saveBOOKING()) {
        printf("Failed to save BOOKING data.\n");
        return; 
    }
    
    printf("BOOKING %s added successfully.\n", BOOKING.roomNumber);
}

void displayBOOKING(char filter[10]) {
    int displayedBOOKING =0 ;
    if (bookingcount == 0) {
        printf("No BOOKINGs available to display.\n");
        return;
    }

    for (int i = 0; i < bookingcount; i++) {
        if (filter != NULL){
            if(strcmp(filter, "AVAILABLE") == 0){
                if(!BOOKINGs[i].isAvailable){
                    continue; // skip print if BOOKING is not available
                }
            }
            else{ //Display by BOOKING number if not NULL /AVAILABLE
                if(strcmp(BOOKINGs[i].roomNumber , filter)!=0)
                    continue;
                }
        }

        if (i == 0) {
            printf("**********************************************\n");
        }
        printf("BOOKING Number: %s details\n", BOOKINGs[i].roomNumber);
        printf("**********************************************\n");
        printf("BOOKING Price: Rs %.2f\n", BOOKINGs[i].price);
        printf("BOOKING Capacity: %d person(s)\n", BOOKINGs[i].capacity);
        printf("BOOKING Available: %s\n", (BOOKINGs[i].isAvailable == 1) ? "Yes" : "No");
        printf("Have Attached BathBOOKING: %s\n", (BOOKINGs[i].isBathBOOKINGAttached == 1) ? "Yes" : "No");
        printf("Have Balcony: %s\n", (BOOKINGs[i].hasBalcony == 1) ? "Yes" : "No");
        printf("**********************************************\n\n");
        displayedBOOKING ++;
    }
    if(!displayedBOOKING){
        printf("BOOKINGs Not available.\n");
    }
    printf("Press any key to continue...\n");
    getchar(); 
}

void updateBOOKINGDetails() {
    BOOKING BOOKING;
    int found =0;
    printf("Enter BOOKING ID to update: ");
    fgets(BOOKING.roomNumber, sizeof(BOOKING.roomNumber), stdin);
    BOOKING.roomNumber[strcspn(BOOKING.roomNumber, "\n")] = 0; 
        for (int i = 0; i < bookingcount; i++) {
            if (strcmp(BOOKINGs[i].roomNumber, BOOKING.roomNumber) == 0) {
                found =1;
                printf("Enter Price for BOOKING %s: ", BOOKING.roomNumber);
                scanf("%f", &BOOKING.price);

                printf("Enter Capacity of People for BOOKING %s: ", BOOKING.roomNumber);
                scanf("%d", &BOOKING.capacity);
                BOOKING.isAvailable = 1;

                do {
                    printf("Is bathBOOKING attached in BOOKING %s? (0 = NO, 1 = YES): ", BOOKING.roomNumber);
                    scanf("%d", &BOOKING.isBathBOOKINGAttached);
                } while (BOOKING.isBathBOOKINGAttached < 0 || BOOKING.isBathBOOKINGAttached > 1);

                do {
                    printf("Does BOOKING %s have a balcony? (0 = NO, 1 = YES): ", BOOKING.roomNumber);
                    scanf("%d", &BOOKING.hasBalcony);
                } while (BOOKING.hasBalcony < 0 || BOOKING.hasBalcony > 1); 
                BOOKINGs[i] = BOOKING; 
                if (!saveBOOKING()) {
                    printf("Failed to save BOOKING data.\n");
                    return; 
                }
 
            }
    }
    if(found){
        printf("BOOKING %s Updated successfully.\n", BOOKING.roomNumber);
    }else{
        printf("BOOKING %s doesnt exists.\n", BOOKING.roomNumber);
    }
    printf("Press any key to continue.");
    getchar();
    
}

void deleteBOOKINGDetails() {
    if (bookingcount == 0) {
        printf("No BOOKINGs available to delete.\n");
        return;
    }

    char roomNumber[10];
    int found = 0;

    printf("Enter BOOKING ID to Delete: ");
    fgets(roomNumber, sizeof(roomNumber), stdin);
    roomNumber[strcspn(roomNumber, "\n")] = 0;

    for (int i = 0; i < bookingcount; i++) {
        if (strcmp(BOOKINGs[i].roomNumber, roomNumber) == 0) {
            found = 1;
            printf("Deleting BOOKING %s...\n", roomNumber);
            for (int j = i; j < bookingcount - 1; j++) {
                BOOKINGs[j] = BOOKINGs[j + 1]; 
            }
            bookingcount--; 

            break;
        }
    }

    if (!found) {
        printf("BOOKING ID %s not found.\n", roomNumber);
        return;
    }
    if (!saveBOOKING()) {
        printf("Failed to save updated BOOKING data.\n");
        return; 
    }
    printf("BOOKING %s deleted successfully.\n", roomNumber);
}
