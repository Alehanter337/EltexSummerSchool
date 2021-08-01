#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define SERVER_CHAT "/server_chat_q"
#define SERVER_DATA "/server_data_q"
#define MSG_BUFF 100
#define ERROR -1
#define SUCCESS 0

void *listen_queue(void *args);

int main(void)
{
    mqd_t data_d;
    mqd_t client_d;
    mqd_t chat_d;
    pid_t pid;
    pthread_t listen_queue_tid;
    char input_box[MSG_BUFF - 15];
    char nick[15];
    char msg[MSG_BUFF + 2];
    char descriptor_buff[20];
    char *curr_char;
    int status_data_q;
    int status_chat_q;
    int status_client_q;
    int listen_queue_status;
    pthread_attr_t pthread_attr;
    pthread_attr_init(&pthread_attr);
    pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_JOINABLE);

    printf("|CLIENT| - Start\n");

    chat_d = mq_open(SERVER_CHAT, O_WRONLY);
    if(chat_d == ERROR)
    {
        handle_error_en(chat_d, "mq_open_chat");
    }
    else
    {
        printf("|CLIENT| - Chat queue opened\n");
    }

    data_d = mq_open(SERVER_DATA, O_WRONLY);
    if(data_d == ERROR)
    {
        handle_error_en(data_d, "mq_open_data");
    }
    else
    {
        printf("|CLIENT| - Data queue opened\n");
    }
    
    pid = getpid();
    sprintf(msg, "%d", pid);
    while (mq_send(data_d, msg, strlen(msg), 0) != 0) {}
    
    status_data_q = mq_close(data_d);
    if(status_data_q == ERROR)
    {
        handle_error_en(status_data_q, "mq_close data");
    }
    else
    {
        printf("|CLIENT| - Data queue close\n");
    } 
    
    printf("Enter nick: ");
    fgets(nick, 10, stdin);
    curr_char = strchr(nick, '\n');
    *curr_char = '\0';
    
    sprintf(descriptor_buff, "/client_%d", pid);
    
    client_d = mq_open(descriptor_buff, O_RDONLY);
    if(client_d == ERROR)
    {
        handle_error_en(client_d, "mq_open client");
    }
    else
    {
        printf("|CLIENT| - Client queue created\n");
    }
    
    listen_queue_status = pthread_create(&listen_queue_tid, &pthread_attr, listen_queue, (void *)&client_d);
    if(listen_queue_status != SUCCESS)
    {
        handle_error_en(listen_queue_status, "create listen_queue");
    }

    printf("__!CHAT!__");

    while (1) 
    {
        fgets(input_box, (MSG_BUFF - 15), stdin);

        if(strcmp(input_box, "/exit\n") == 0)
        {
            break;
        }
        else
        {
            printf("\033[A\33[2K\r");
            sprintf(msg, "%s: %s", nick, input_box);
            while (mq_send(chat_d, msg, strlen(msg), 0) != 0) {}
            memset(msg, 0, sizeof(msg));
            memset(input_box, 0, sizeof(input_box));    
        } 
    }
    
    status_chat_q = mq_close(chat_d);
    if(status_chat_q == ERROR)
    {
        handle_error_en(status_chat_q, "mq_close chat");
    }
    else
    {
        printf("|CLIENT| - Chat queue close\n");
    }
    
    status_client_q = mq_close(client_d);
    if(status_client_q == ERROR)
    {
        handle_error_en(status_data_q, "mq_close client");
    }
    else
    {
        printf("|CLIENT| - Client queue close\n");
    }

    printf("|CLIENT| - Finish\n");
    exit(EXIT_SUCCESS);
}

void *listen_queue(void *args)
{
    mqd_t client_d = *((mqd_t *)args);
    char input_box[MSG_BUFF];
    
    while(1)
    {
        if(mq_receive(client_d, input_box, MSG_BUFF, NULL) > 0)
        {
            printf("%s", input_box);
            memset(input_box, 0, sizeof(input_box));
        }
    }
    
    return SUCCESS;
}
