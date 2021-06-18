#include <stdlib.h>
#include <time.h>
unsigned long getTelephoneNumber(int i) {
    srand(i);
    return 80000000000 + rand() % 10000000000;
}
