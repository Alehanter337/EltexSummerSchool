#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


int main(void)
{
    int fd[2];
    char s[100];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        perror("pipe error\n");
        exit(-1);
    }
    
    switch (pid = fork()) 
    {
        case -1:
        {
            perror("fork error");
            exit(-2);
        }
        case 0:
        {
            close(fd[0]);
            printf("Input string: ");
            fgets(s, sizeof(s), stdin);
            if (write(fd[1], &s, sizeof(s)) == -1) 
            {
                perror("Error writing to the pipe\n");
                exit(-3);
            }
            close(fd[1]);
            break;
        }
        default:
        {
            close(fd[1]);
            char s_main[100];
            if(read(fd[0], &s_main, sizeof(s_main)) == -1) 
            {
                perror("Error reading from the pipe\n");
                exit(-4);
            }
            close(fd[0]);
            printf("String from childe process: %s", s_main);
            wait(NULL);
        }
    }
    return 0;
}

