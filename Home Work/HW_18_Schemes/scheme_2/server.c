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
    int port = 7331;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int val = 0;

    int fd_socket = socket(AF_INET, SOCK_STREAM, val);
    if(fd_socket == ERROR)
    {
        handle_error("socket()");
    }
    else
    {
        printf("|SERVER| - Socket created\n");
    }

    int req = bind(fd_socket, (const struct sockaddr *) &server,
                  sizeof(struct sockaddr_in));

    if(req == ERROR)
    {
        handle_error("bind()");
    }
    else
    {
        printf("|SERVER| - Bind complete\n");
    }

    if(listen(fd_socket, 1) == ERROR)
    {
        handle_error("listen()");
    }
    else
    {
        printf("|SERVER| - Listen done\n");
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
            printf("|SERVER| - Pthread create\n");
        }
        
        threads_available[i] = AVAILABLE;
    }

    for(int i = 0; ; i++)
    {
        if(i == NUM_OF_THREADS)
        {
            i = 0;
        }

        if(threads_available[i] != AVAILABLE)
        {
            continue;
        }
        
        fd_data[i] = accept(fd_socket, NULL, NULL);
        if(fd_data[i] == ERROR)
        {
            handle_error("accept()");
        }
        else
        {
            printf("|SERVER| - Accept complete\n");
        }

        char buff[8] = {0};
        sprintf(buff, "%d", fd_data[i]);
        if (mq_send(queues[i], buff, strlen(buff) + 1, 5) == -1)
        {
            handle_error("mq_send()");
        }
        else
        {
            printf("|SERVER| - MSG send\n");
        }

        threads_available[i] = 0;

        printf("|SERVER| - Send data [%d];\n|SERVER| - Thread [%d]\n", fd_data[i], i);
    }


    close(fd_socket);
    exit(EXIT_SUCCESS);
}

void *thread_func(void *param)
{
    struct param_for_threads *threads_params = (struct param_for_threads *)param;
    
    mqd_t fd_queue = mq_open(threads_params->queue_name, O_RDONLY);
    if(fd_queue == 1)
    {
        handle_error("mq_open()");
    }
    else
    {
        printf("|SERVER - Thread| - Queue open\n");
    }

    while(1)
    {
        char buff_2[MAX_MSG_SIZE] = {0};
        if (mq_receive(fd_queue, buff_2, BUFFER_SIZE, NULL) == ERROR)
        {
            handle_error("mq_receive");
        }
        else
        {
            printf("|SERVER - Thread| - Mq_receive\n");
        }

        int fd_data = atoi(buff_2);
        printf("|SERVER - Thread| - FD_DATA - received =%d\n", fd_data);
        
        while(1)
        {
            char buff_3[MAX_MSG_SIZE] = {0};
            int ret = recv(fd_data, buff_3, MAX_MSG_SIZE, 0);
            if(ret == ERROR)
            {
                handle_error("recv()");
            }
            else
            {
                printf("|SERVER -THREAD| - Recv done[%s]\n", buff_3);
            }

            if (strncmp(buff_3, "/exit", MAX_MSG_SIZE) == 0) 
            {
                 close(fd_data);
                 threads_available[threads_params->ID] = AVAILABLE;
                 break;
            }

            strcat(buff_3, " from SERVER\n");

            ret = send(fd_data, buff_3, MAX_MSG_SIZE, 0);
            if(ret == ERROR)
            {
                handle_error("send()");
            }
            else
            {
                printf("|SERVER - THREAD| - Send done\n");
            }

            printf("|SERVER - THREAD| - MSG: %s\n", buff_3);
        }
    }
}
