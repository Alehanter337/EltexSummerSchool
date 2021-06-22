#include <stdlib.h>
#include <time.h>

char *lastnameBase[] = {
                        "Hartley",
                        "Mair",
                        "Abbott",
                        "Clegg",
                        "Jackson",
                        "Ferreira",
                        "Blevins",
                        "Kirk",
                        "Palmer",
                        "Mckeown"
};

char* getLastName(int i){
    srandom(i);
    return lastnameBase[rand()%10];
}

