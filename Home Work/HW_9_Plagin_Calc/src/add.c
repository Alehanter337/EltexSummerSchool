#include "main.h"

int add(int a, int b) {
	return a + b;
}

char* get_lib_name() {
	char *lib_name = (char*) malloc(5 * sizeof(char));
	if (lib_name == NULL) exit (1);
    strcpy(lib_name, "add\0");
	return lib_name;
}

