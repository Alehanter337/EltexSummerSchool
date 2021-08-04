#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <mqueue.h>

#define PORT 7331

#define BUFFER_SIZE MAX_MSG_SIZE + 10

#define SUCCESS 0

#define ERROR -1

#define IS_EMPTY -1

#define MAX_SOCKET_VALUE 100

#define MAX_MESSAGES 10

#define QUEUE_PERMISSIONS 0777

#define MAX_MSG_SIZE 256

#define NUM_OF_THREADS 10

#define AVAILABLE 1

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct param_for_threads
{
    int ID;
    char *queue_name;
};

void *thread_func(void *);

#endif
