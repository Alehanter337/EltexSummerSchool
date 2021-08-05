#include "headers.h"
#include <mqueue.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

short int threads_available[NUM_OF_THREADS];

int main(void)
{
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int fd_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_socket == ERROR)
    {
        handle_error("socket()");
    }
    else 
    {
        printf("|SERVER| - Socket created\n");
    }

    if(bind(fd_socket, (const struct sockaddr *) &server,
            sizeof(struct sockaddr_in)) == ERROR)
    {
        handle_error("bind()");
    }
    else
    {
        printf("|SERVER| - Bind complete\n");
    }
    
    if(listen(fd_socket, 5) == ERROR)
    {
        handle_error("listen()");
    }
    else
    {
        printf("|SERVER| - Listen complete\n");
    }

    pthread_attr_t thread_attr_default;
    pthread_attr_init(&thread_attr_default);
    
    struct mq_attr queue_attr;
    queue_attr.mq_flags = 0;
    queue_attr.mq_maxmsg = MAX_MESSAGES;
    queue_attr.mq_msgsize = MAX_MSG_SIZE;
    queue_attr.mq_curmsgs = 0;

    pthread_t threads[NUM_OF_THREADS];
    int fd_data[NUM_OF_THREADS] = {0};    
    mqd_t queues[NUM_OF_THREADS];
    char **queues_names = malloc(sizeof(char *) * NUM_OF_THREADS);
    struct param_for_threads threads_params[NUM_OF_THREADS];
    
    for(int i = 0; i < NUM_OF_THREADS; i++)
    {
        queues_names[i] = malloc(sizeof(char) * 32);
        sprintf(queues_names[i], "/client_%d", i);
        queues[i] = mq_open(queues_names[i], O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, &queue_attr);
        if(queues[i] == ERROR)
        {
            handle_error("mq_open()");
        }
        else
        {
            printf("|SERVER| - mq_open conf\n");
        }
        
        threads_params[i].ID = i;
        threads_params[i].queue_name = queues_names[i];
        void *param = (void *)&threads_params[i];

        if (pthread_create(&threads[i], &thread_attr_default, thread_func, param))
        {
            handle_error("pthread_create()");
        }
        else
        {
            printf("|SERVER| - Pthrad create\n");
        }
        
        threads_available[i] = AVAILABLE;
    }

    for(int i = 0; ; i++)
    {
        if(i == NUM_OF_THREADS)
        {
            i = 0;
        }
    }


    close(fd_socket);
    exit(EXIT_SUCCESS);
}
