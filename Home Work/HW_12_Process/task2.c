#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

#define NUM_OF_CHILD_PROC 2
#define TREE_LVL_MAX 2

enum Branches
{
	LEFT_BRANCH,
	RIGHT_BRANCH
};

struct Process_data {
    pid_t pid;
    pid_t ppid;
};

void parent_wait(int n, pid_t *pid)
{
	int i, status, stat;
    struct Process_data parent;
    parent.pid = getpid();
	parent.ppid = getppid();
	printf("PARENT: pid: %d\n", parent.pid);
	printf("PARENT: ppid: %d\n", parent.ppid);
	for(i = 0; i < n; i++)
	{
		status = waitpid(pid[i], &stat, 0);
		if (pid[i] == status)
			printf("PARENT process %d completed with status = %d\n", i, WEXITSTATUS(stat));
	}
}

void make_process(int curr_lvl)
{
	struct Process_data child;
	int num_of_proc = 1;
	switch (child.pid = fork()) {
	    case -1:
            perror("fork = -1");
            exit(EXIT_FAILURE);
        case 0:
            curr_lvl++;
			child.pid = getpid();
			child.ppid = getppid();
			printf(">>CHILD: pid: %d\n", child.pid);
			printf(">>CHILD: ppid: %d\n", child.ppid);
			exit(EXIT_SUCCESS);
        default:
            parent_wait(num_of_proc, &child.pid);
	}
}


void make_processes(int curr_lvl)
{
	pid_t pid[NUM_OF_CHILD_PROC];
    
    struct Process_data child;
    
	for (int i = 0; i < NUM_OF_CHILD_PROC; i++) 
	{
		switch(pid[i] = fork()) {
		    case -1:
			    perror("fork");
			    exit(EXIT_FAILURE);
            case 0:
				curr_lvl++;
				child.pid = getpid();
				child.ppid = getppid();
				printf(">CHILD: pid: %d\n", child.pid);
				printf(">CHILD: ppid: %d\n", child.ppid);
			    
                if(curr_lvl < TREE_LVL_MAX)
                {
                    switch (i) 
                    {
                        case LEFT_BRANCH: make_processes(curr_lvl);
                        case RIGHT_BRANCH: make_process(curr_lvl);
                    }
                }
                exit(EXIT_SUCCESS); 
			}
	}
	parent_wait(NUM_OF_CHILD_PROC, pid);
}

int main(void) 
{
	int curr_lvl = 0;
	make_processes(curr_lvl);
	return 0;
}
