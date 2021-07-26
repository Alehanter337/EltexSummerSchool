#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <linux/limits.h>
#include <pwd.h>

#define MAX_LEN 128

void print_start_image();

typedef enum {false, true} bool;

int main(void)
{
    char dir[PATH_MAX];
    char comm[ARG_MAX];
    char *curr_char; 
    char *args_1[MAX_LEN];    
    char *args_2[MAX_LEN];
    int args_flag = false;
    char *pipe_flag = NULL;
    short shift = 0;
    int args_count = 1;
    int fd[2];
    pid_t pid[2];
    struct passwd *userinfo;
    uid_t userid;
    userinfo = getpwuid(userid);

    print_start_image(); 
    
    while(1)
    {  
        if (getcwd(dir, PATH_MAX) == NULL)
        {
            fprintf(stderr, "error: getcwd fail\n");
            exit(EXIT_FAILURE);
        }
        else if (userinfo == NULL) 
        {
            fprintf(stderr, "error: userinfo fail\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("%s:%s -> ",userinfo->pw_name, dir);
        }

        fgets(comm, ARG_MAX, stdin);
        curr_char = strchr(comm, '\n');
        *curr_char = '\0';
        
        if(comm[0] == '\0')
        {
            continue;
        }
        
        if(strcmp(comm, "quit") == 0)
        {
            exit(EXIT_SUCCESS);
        }
             
        if((*args_1 = strtok(comm, "|")) == NULL)
        {
            fprintf(stderr, "error: string cannot be split\n");
            exit(EXIT_FAILURE);
        }
        if((pipe_flag = strtok(NULL, "|")) != NULL)
        {
            args_flag = true;
            while(pipe_flag[shift] == ' ')
            {
                shift++;
            }
            *args_2 = pipe_flag + shift;
        }
         
        for(curr_char = *args_1; *curr_char != 0; curr_char++)
        {
            if((*curr_char == ' ') && (((*curr_char) + 1) != ' '))
            {
                *curr_char= '\0';
                args_1[args_count] = curr_char + 1;
                args_count++;
            } 
        }

        if(args_flag == true)
        {
            args_1[args_count - 1] = NULL;
            args_count = 1;
            
            for(curr_char = *args_2; *curr_char != 0; curr_char++)
            {
                if((*curr_char == ' ') && (((*curr_char) + 1) != ' '))
                {
                    *curr_char = '\0';
                    args_2[args_count] = curr_char + 1;
                    args_count++;
                }
            }
            pipe(fd);
        }
        
        switch (pid[0] = fork()) 
        {
            case -1:
            {
                fprintf(stderr, "error: fork fail\n");
                exit(EXIT_FAILURE);
            }
            case 0:
            {
                if(args_flag == true)
                {
                    dup2(fd[1], 1);
                    close(fd[0]);
                    close(fd[1]);
                }

                if(execvp(*args_1, args_1) == -1)
                {
                    fprintf(stderr, "error: execvp fail\n");
                    exit(EXIT_FAILURE);
                }
                
            }
        }
        
        if(args_flag == true)
        {
            switch (pid[1] = fork()) 
            {
                case -1:
                {
                    fprintf(stderr, "error: fork2 fail\n");
                    exit(EXIT_FAILURE);
                }
                case 0:
                {
                    dup2(fd[0], 0);
                    close(fd[0]);
                    close(fd[1]);
                }

                if(execvp(*args_2, args_2) == -1)
                {
                    fprintf(stderr, "error: execvp2:while fail\n");
                    exit(EXIT_FAILURE);
                }
                
            }
        }

        waitpid(pid[0], NULL, WUNTRACED);
        if(args_flag == true)
        {
            waitpid(pid[1], NULL, WNOHANG);
            close(fd[0]);
            close(fd[1]);
        }
    }

    return 0;
}
    
void print_start_image()
{
    //Файл с ASCII image
    char *filename = "image.txt";
    FILE *fptr = NULL;
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        exit(EXIT_FAILURE);
    }
    char read_string[MAX_LEN];
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
    {
        printf("%s",read_string);
    }
    fclose(fptr);
}

