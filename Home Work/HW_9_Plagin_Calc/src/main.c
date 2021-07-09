#include "main.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	
    int (**lib_ptr)(int, int);

	lib_ptr = (int (**)(int,  int)) malloc(argc * sizeof(int*));
	
    char **lib_name = (char**) malloc(argc * sizeof(char*)); 

    for (int i = 1; i < argc; i++) {
		
        void *libhandle = dlopen(argv[i], RTLD_LAZY);
		
        if (libhandle == NULL) {
			fputs(dlerror(), stderr);
			exit(1);
		}
		
		char *(*curr_fn)(); 
		curr_fn = dlsym(libhandle, "get_lib_name");
		
        if ((*curr_fn)() == NULL) {
			fputs(dlerror(), stderr);
			exit(2);
		}

		lib_name[i] = curr_fn();
		
        lib_ptr[i] = dlsym(libhandle, lib_name[i]);
		
        if (lib_ptr[i] == NULL) {
			fputs(dlerror(), stderr);
			exit(3);
		}
	}
    
    int opt = 0, a = 0, b = 0;

	while (1) {
		
		printf("Options:\n"); 
		
        for (int i = 1; i < argc; i++) {
			printf("%d) %s \n", i, lib_name[i]);
		}

        printf("Choose option\n");
        scanf("%d", &opt);

        if (opt >= 1 && opt < argc) {
            printf("Enter a\n->");        
		    scanf("%d", &a);
            printf("Enter b\n->");
		    scanf("%d", &b);
            printf("RESULT of option %s = %d\n", lib_name[opt], lib_ptr[opt](a, b));
        }
        else
            printf("No options\n");
        
        char f = 'y';
		printf("Choose y or n to continue\n");
		scanf("\n%c", &f);
		
        if(f == 'n')
            break;
        else
            continue;
	}

	return 0;
}
