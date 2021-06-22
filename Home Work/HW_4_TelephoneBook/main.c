#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "getFirstName.h"
#include "getLastName.h"
#include "getTelephoneNumber.h"

#define n 50

struct subscriber {
    short id;
    char firstname[25];
    char lastname[25];
    unsigned long telephoneNumber;
};

void showSubscribers(struct subscriber[], int); 
void addSubscriber(struct subscriber subscribers[n]); 
void deleteSubscriber(struct subscriber subscribers[n]); 
void getMenu();



void getMenu() {
    printf("Select an action from the list\n");
    printf("1: Show subscribers\n");
    printf("2: Add subscriber\n");
    printf("3: Delete subscribers\n");
    printf("4: Search subscriber\n"); 
    printf("5: Exit\n");
    printf("->");
}

int getValidValue(int num) {
    int value;
    char stringMenu[50];
    scanf("%s", stringMenu);
    
    while(
        sscanf(stringMenu, "%d", &value) !=1 || 
        value < 1 || 
        value > num
    ) {
        printf("Incorrect entry, select an emergency from the list: ");
        scanf("%s", stringMenu);
    }

    return value;
}

void showSubscribers(struct subscriber subscribers[n], int size) {
    printf("|----|----------------|---------------|------------------|\n");
    printf("| ID |   First Name   |   Last Name   |   Phone Number   |\n");
    printf("|----|----------------|---------------|------------------|\n");

    if (size == 0)
        printf("|                     No Subs                       |\n");
    
    for(int i = 0; i < size; i++){
        printf(
                "| %2d | %14s | %13s | %16ld |\n",
                subscribers[i].id, 
                subscribers[i].firstname, 
                subscribers[i].lastname, 
                subscribers[i].telephoneNumber
              );
    }
    printf("|____|________________|_______________|__________________|\n");

}

void addSubscriber(struct subscriber subscribers[n]) {
    int num = 0;
    printf("Enter ID which is empty\n");
    scanf("%d", &num);
    if(subscribers[num].telephoneNumber == 0) {
        printf("Enter firstname: ");
        scanf("%s", subscribers[num].firstname);
        printf("Enter lastname: ");
        scanf("%s", subscribers[num].lastname);
        printf("Enter phone number: ");
        scanf("%lu", &subscribers[num].telephoneNumber);
    } 
    else
        printf("Place Taken\n");   
}

void deleteSubscriber(struct subscriber subscribers[n]) {
    int num = 0;
    printf("Enter the ID you want to remove: ");
    scanf("%d", &num);
    
    if(subscribers[num].telephoneNumber != 0) {
        strcpy(subscribers[num].firstname, "0");
        strcpy(subscribers[num].lastname, "0");
        subscribers[num].telephoneNumber = 0;
    }
    else
        printf("ID is empty");
}


void search(struct subscriber subscribers[n]) {
     unsigned long phoneNumber;
     short c = 0;
     printf("Enter phone number\n");         
     scanf("%lu", &phoneNumber);
     
     for(int i = 0; i < n; i++) {
        if(phoneNumber == subscribers[i].telephoneNumber) {
            printf("|----|----------------|---------------|------------------|\n");
            printf("| ID |   First Name   |   Last Name   |   Phone Number   |\n");
            printf("|----|----------------|---------------|------------------|\n");
            printf(
                "| %2d | %14s | %13s | %16ld |\n",
                subscribers[i].id, 
                subscribers[i].firstname, 
                subscribers[i].lastname, 
                subscribers[i].telephoneNumber
            );
            printf("|____|________________|_______________|__________________|\n");
            c++;
            break;
        }
     }
     if (c == 0)
        printf("No Data\n");     
}


int main() {
    srand(time(NULL));
    int value;
    int size = n;
    struct subscriber subscribers[n];
    
    for(int i = 0; i < size; i++) {
        subscribers[i].id = i;
        strcpy(subscribers[i].firstname, getFirstName(i));
        strcpy(subscribers[i].lastname, getLastName(i));
        subscribers[i].telephoneNumber = getTelephoneNumber(i);
    }
    
    do {
        getMenu();

        value = getValidValue(5);

        switch (value) {
        
            case 1:
                showSubscribers(subscribers, size);
                break;

            case 2:
                addSubscriber(subscribers);
                break;

            case 3:
                deleteSubscriber(subscribers);
                break;

            case 4:
                search(subscribers);
                break;
        }
    
    } while (value != 5);  
    
    return 0;
}
