#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct subscriber {
    short id;
    char firstname[25];
    char lastname[25];
    unsigned long telephone_number;
} subscriber;

void get_menu() {
    printf("Select an action from the list\n");
    printf("1: Show subscribers\n");
    printf("2: Add subscriber\n");
    printf("3: Delete subscribers\n");
    printf("4: Search subscriber\n"); 
    printf("5: Exit\n");
    printf("->");
}

int get_valid_value(int num) {
    int value;
    char string_menu[50];
    scanf("%s", string_menu);
    while(
        sscanf(string_menu, "%d", &value) !=1 || 
        value < 1 || 
        value > num
    ) {
        printf("Incorrect entry, select an emergency from the list: ");
        scanf("%s", string_menu);
    }
    return value;
}

void show_subscribers(struct subscriber *subscribers, int size) {
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
                subscribers[i].telephone_number
              );
    }
    printf("|____|________________|_______________|__________________|\n");

}

void add_subscriber(struct subscriber **subscribers, int *size, int *capacity) {
    printf("Enter firstname: ");
    scanf("%s", &(*subscribers)[*size].firstname);
    printf("Enter lastname: ");
    scanf("%s", &(*subscribers)[*size].lastname);
    printf("Enter phone number: ");
    scanf("%lu", &(*subscribers)[*size].telephone_number);
    (*size)++;
    if (*size >= *capacity) {
        *capacity *= 2;

        *subscribers = (struct subscriber *)realloc(*subscribers, *capacity * sizeof(subscriber));
    }
       
}

void delete_subscriber(struct subscriber *subscribers) {
    int num = 0;
    printf("Enter the ID you want to remove: ");
    scanf("%d", &num);
    
    if(subscribers[num].telephone_number != 0) {
        strcpy(subscribers[num].firstname, "0");
        strcpy(subscribers[num].lastname, "0");
        subscribers[num].telephone_number = 0;
    }
    else
        printf("ID is empty");
}


void search(struct subscriber *subscribers, int size) {
     unsigned long phone_number_search;
     short c = 0;
     printf("Enter phone number\n");         
     scanf("%lu", &phone_number_search);
     
     for(int i = 0; i < size; i++) {
        if(phone_number_search == subscribers[i].telephone_number) {
            printf("|----|----------------|---------------|------------------|\n");
            printf("| ID |   First Name   |   Last Name   |   Phone Number   |\n");
            printf("|----|----------------|---------------|------------------|\n");
            printf(
                "| %2d | %14s | %13s | %16ld |\n",
                subscribers[i].id, 
                subscribers[i].firstname, 
                subscribers[i].lastname, 
                subscribers[i].telephone_number
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
    int value;
    int size = 0;
    int capacity = 1;

    struct subscriber* subscribers = (struct subscriber *)malloc(capacity * sizeof(subscriber));

    do {
        get_menu();

        value = get_valid_value(5);

        switch (value) {
        
            case 1:
                show_subscribers(subscribers, size);
                break;

            case 2:
                add_subscriber(&subscribers, &size, &capacity);
                break;

            case 3:
                delete_subscriber(subscribers);
                break;

            case 4:
                search(subscribers, size);
                break;
        }
    
    } while (value != 5);  
    
    return 0;
}
