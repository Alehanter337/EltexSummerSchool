#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>

#define SERVER_CHAT "/server_chat_q"

typedef struct 
{
    pid_t pid[5];
    unsigned short client_count;
    mqd_t server_d;
    mqd_t client_d;
    mqd_t chat_d;
} shed;

int main(void)
{
    shed args;
    pthread_t server_tid;
    pthread_t client_tid;
    pthread_t chat_tid;
    
    printf("SERVER - Start\n");
    
    while ((args.chat_d = mq_open(SERVER_CHAT, O_RDONLY, 777, NULL)) == -1){}

}
