#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {

    pid_t pid, ppid;
    int status_code = 0;
    switch(pid = fork()) {
        case -1:
            perror("fork = -1");
            exit(1);
        case 0:
            printf(">--CHILD-- : Процесс потомок \n");
            printf(">--CHILD-- : PID -- %d\n", getpid());
            printf(">--CHILD-- : PID родителя -- %d\n", getppid());
            printf(">--CHILD-- : Выход!\n");
            exit(status_code);
        default:
            printf("--PARENT-- : Процесс родитель!\n");
            printf("--PARENT-- : PID -- %d\n", getpid());
            printf("--PARENT-- : PID потомка %d\n",pid);
            wait(NULL);
            printf("--PARENT-- : Код возврата потомка: %d\n", WEXITSTATUS(status_code));
            printf("--PARENT-- : Выход!\n");
    }

}
