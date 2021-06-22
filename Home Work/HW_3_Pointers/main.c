#include <stdio.h>

int main() {
    
    unsigned int a = 442424242;

    char *ptr;

    ptr = (char *)&a;
    
    for(int i = 0; i < sizeof(a); i++) {
        printf("%d byte of a = %d\n",i , *ptr);
        ptr++;
    }
    
    printf("\n");

    ptr = ptr - 3;
    *ptr = 42;
    
    for(int i = 0; i < sizeof(a); i++) {
        printf("%d byte of a = %d\n",i , *ptr);
        ptr++;
    }
    
    printf("\n");

    printf("number a = %d\n", a);
    
    return 0;
}
