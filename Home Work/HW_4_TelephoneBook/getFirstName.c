#include <stdlib.h>
#include <time.h>

char *firstnameBase[] = {
                            "Dalton", 
                             "Katie",
                             "Taha",
                             "Indiana",
                             "Salman",
                             "Affan",
                             "Tia",
                             "Samirah",
                             "Anayah",
                             "Norman"
};



char *getFirstName(int i){
    srand(i);
    return firstnameBase[rand()%10];
}

