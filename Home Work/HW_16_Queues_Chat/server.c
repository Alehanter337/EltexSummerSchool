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
#define SERVER_DATA "/serve_data_q"
#define MAX_CLIENTS 10
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
    mqd_t client_d[MAX_CLIENTS];
    mqd_t chat_d;
} shed;

struct mq_attr queue_attr;

int main(void)
{
    shed args;
    pthread_t data_tid;
    pthread_t input_msg_tid;
    pthread_t chat_tid;
    int status_data;
    int status_input_msg;
    int status_chat;
    void *res_data;
    void *res_input;
    void *res_chat;
    int status_chat_q;
    int status_data_q;
    int status_client_q;
    char curr_client_queue_buff[15];

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
    
    args.data_d = mq_open(SERVER_DATA, O_RDONLY | O_CREAT, 0777, &queue_attr);

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
        printf("|SERVER| - All threads was canceled\n");
    }
    else
    {
        printf("|SERVER| - Thread or threads wasn't canceled (shouldn't happen!)\n");
    }

    status_chat_q = mq_close(args.chat_d);
    if(status_chat_q == ERROR)
    {
        handle_error_en(status_chat_q, "mq_close chat");
    }
    else
    {
        printf("|SERVER| - Chat queue close\n");
    }
    
    status_chat_q = mq_unlink(SERVER_CHAT);
    if(status_chat_q == ERROR)
    {
        handle_error_en(status_chat_q, "mq_unlink chat");
    }
    else 
    {
        printf("|SERVER| - Chat queue unlink\n");
    }

    status_data_q = mq_close(args.data_d);
    if(status_data_q == ERROR)
    {
        handle_error_en(status_data_q, "mq_close data");
    }
    else
    {
        printf("|SERVER| - Data queue close\n");
    }
    
    status_data_q = mq_unlink(SERVER_DATA);
    if(status_data_q == ERROR)
    {
        handle_error_en(status_data_q, "mq_unlink data");
    }
    else 
    {
        printf("|SERVER| - Data queue unlink\n");
    }

    for(int i = 0; i < args.client_count; i++)
    {
        
        status_client_q =  mq_close(args.client_d[i]);
        if(status_client_q == ERROR)
        {
            handle_error_en(status_client_q, "mq_close client");
        }
        else
        {
            sprintf(curr_client_queue_buff,"/client_%d", args.pid[i]);
            printf("|SERVER| - Client[%d] queue close", args.pid[i]);
        }
        
        status_client_q = mq_unlink(curr_client_queue_buff);
        if(status_client_q == ERROR)
        {
            handle_error_en(status_client_q, "mq_unlink client");
        }
        else 
        {
            printf("|SERVER| - Client[%d]  unlink\n", args.pid[i]);
        }
    }
    
    printf("|SERVER| - Finish\n");
    exit(EXIT_SUCCESS);
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
