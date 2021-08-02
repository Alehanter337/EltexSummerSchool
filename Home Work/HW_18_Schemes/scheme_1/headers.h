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

#define BUFFER_SIZE 256

#define SUCCESS 0

#define ERROR -1

#define IS_EMPTY -1

#define MAX_SOCKET_VALUE 100

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

#endif
