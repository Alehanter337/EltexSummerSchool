#include <stdio.h>

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
