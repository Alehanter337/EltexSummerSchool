#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int main(void) {
    pid_t pid;

    switch(pid = fork()) {
        
        case -1:
            
            perror("fork == -1");
            exit(EXIT_FAILURE);
        
        case 0:
            
            if(execl("./test_exec","test_exec", NULL) < 0) {
			    perror("execl < 0");
			    exit(EXIT_FAILURE);
		    }

	    default:
		    
            if(wait(NULL) == -1) {
			    perror("wait == -1");
			    exit(EXIT_FAILURE);
		    }

		    printf("CHILD: pid = %d\n", pid);
		    printf("PARENT: pid = %d\n", getpid());
		    exit(EXIT_SUCCESS);
    }
}
