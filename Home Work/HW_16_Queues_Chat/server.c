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
#define MQ_MSG 10
#define MQ_BUFF_SIZE 100
#define SUCCESS 0
#define ERROR -1

void* listen_data(void *args);
void* listen_chat(void *args);
void* listen_input_msg();

typedef struct 
{
    pid_t pid[5];
    unsigned short client_count;
    mqd_t data_d;
    mqd_t client_d;
    mqd_t chat_d;
} shed;

struct mq_attr queue_attr;

int main(void)
{
    shed args;
    pthread_t data_tid;
    pthread_t input_msg_tid;
    pthread_t chat_tid;
    int status_data = 0;
    int status_input_msg = 0;
    int status_chat = 0;
    void *res_data;
    void *res_input;
    void *res_chat;

    queue_attr.mq_flags = 0;
    queue_attr.mq_maxmsg = MQ_MSG;
    queue_attr.mq_msgsize = MQ_BUFF_SIZE;
    queue_attr.mq_curmsgs = 0;
    
    args.client_count = 0;

    printf("|SERVER| - Start\n");
    
    
    args.chat_d = mq_open(SERVER_CHAT, O_RDONLY | O_CREAT, 0777, &queue_attr);
    
    if(args.chat_d == ERROR) 
    {
        handle_error_en(args.chat_d, "mq_open");
    }
    else
    {
        printf("|SERVER| - Chat queue created\n");
    }
    
    args.data_d = mq_open(SERVER_CHAT, O_RDONLY | O_CREAT, 0777, &queue_attr);

    if(args.chat_d == ERROR) 
    {
        handle_error_en(args.chat_d, "mq_open_data");
    }
    else
    {
        printf("|SERVER| - Data queue created\n");
    }
    
    status_data = pthread_create(&data_tid, NULL, listen_data, (void *) &args);
    if(status_data != SUCCESS)
    {
        handle_error_en(status_data, "create data_ptrhead");
    }
    
    status_chat = pthread_create(&chat_tid, NULL, listen_chat, (void *) &args);
    if(status_chat != SUCCESS)
    {
        handle_error_en(status_chat, "create chat_ptrhead");
    }
    
    status_input_msg = pthread_create(&input_msg_tid, NULL, listen_input_msg, NULL);
    if(status_input_msg != SUCCESS)
    {
        handle_error_en(status_input_msg, "create input_ptrhead");
    }
    
    status_input_msg = pthread_cancel(input_msg_tid);
    if(status_input_msg != SUCCESS)
    {
        handle_error_en(status_input_msg, "cancel input_ptrhead");
    }

    status_data = pthread_cancel(data_tid);
    if(status_data != SUCCESS)
    {
        handle_error_en(status_data, "cancel data_ptrhead");
    }

    status_chat = pthread_cancel(chat_tid);
    if(status_chat != SUCCESS)
    {
        handle_error_en(status_chat, "cancel chat_ptrhead");
    }

    status_input_msg = pthread_join(input_msg_tid, &res_input);
    if(status_input_msg != SUCCESS)
    {
        handle_error_en(status_input_msg, "join input_ptrhead");
    }

    status_data = pthread_join(data_tid, &res_chat);
    if(status_data != SUCCESS)
    {
        handle_error_en(status_data, "join data_ptrhead");
    }
    
    status_chat = pthread_join(chat_tid, &res_data);
    if(status_chat != SUCCESS)
    {
        handle_error_en(status_chat, "join chat_ptrhead");
    }
    
    if (res_input == PTHREAD_CANCELED && res_data == PTHREAD_CANCELED && res_chat == PTHREAD_CANCELED)
    {
        printf("main(): all threads was canceled\n");
    }
    else
    {
        printf("main(): thread or threads wasn't canceled (shouldn't happen!)\n");
    }
}

void* listen_data(void *args)
{
    sleep(3);
    return SUCCESS;
}

void* listen_chat(void *args)
{
    sleep(3);
    return SUCCESS;
}

void* listen_input_msg()
{
    sleep(3);
    return SUCCESS;
}
