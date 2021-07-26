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
    char *args_1;    
    char *args_2;
    int args_flag = false;
    char *pipe_flag = NULL;
    struct passwd *userinfo;
    uid_t userid;
    userinfo = getpwuid(userid);

    print_start_image(); 
    
    while(1)
    {  
        if (getcwd(dir, PATH_MAX) == NULL)
        {
            fprintf(stderr, "error: getcwd fail");
            exit(EXIT_FAILURE);
        }
        else if (userinfo == NULL) 
        {
            fprintf(stderr, "error: userinfo fail");
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
            printf("bye\n");
            exit(0);
        }
        
        
        args_1 = (char*)malloc(strlen(comm));
             
        if((args_1 = strtok(comm, "|")) == NULL)
        {
            fprintf(stderr, "error: string cannot be split");
            exit(EXIT_FAILURE);
        }
        else if((pipe_flag = strtok(NULL, "|")) != NULL)
        {
            printf("more pipes\n");
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

