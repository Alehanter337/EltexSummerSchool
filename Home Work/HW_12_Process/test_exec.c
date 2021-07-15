#include <stdio.h>
#include <unistd.h>

struct Process {
    pid_t pid;
    pid_t ppid;
};

int main(void) {
    struct Process proc;
    proc.pid = getpid();
    proc.ppid = getppid();
    printf("CHILD: pid = %d, ppid = %d\n", proc.pid, proc.ppid);
    return 0;
}
