#include <stdio.h>
#include "calc.h"
#include "getMenu.h"
#include "getValidValue.h"

int main(void) {
    int value = 0;
    float rez = 0;
    float a, b = 0;
    do {
        
        printf("Enter first num: ");
        scanf("%f", &a);
        printf("Enter second num: ");
        scanf("%f", &b);
        
        get_menu();

        value = get_valid_value(5);
        
        switch (value) {
            
            case 1:
                rez = add(a, b);
                printf("%f\n", rez);
                break;
            
            case 2:
                rez = minus(a, b);
                printf("%f\n", rez);
                break;

            case 3:
                rez = multiply(a, b);
                printf("%f\n", rez);
                break;

            case 4:
                rez = divide(a, b);
                printf("%f\n", rez);
                break;
        }
    
    } while (value != 5);    
}
