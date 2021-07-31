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

    pthread_attr_t pthread_attr;
    pthread_attr_init(&pthread_attr);
    pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_JOINABLE);

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

    status_data = pthread_create(&data_tid, &pthread_attr, listen_data, (void *) &args);
    if(status_data != SUCCESS)
    {
        handle_error_en(status_data, "create data_ptrhead");
    }

    status_chat = pthread_create(&chat_tid, &pthread_attr, listen_chat, (void *) &args);
    if(status_chat != SUCCESS)
    {
        handle_error_en(status_chat, "create chat_ptrhead");
    }

    status_input_msg = pthread_create(&input_msg_tid, &pthread_attr, listen_input_msg, NULL);
    if(status_input_msg != SUCCESS)
    {
        handle_error_en(status_input_msg, "create input_ptrhead");
    }
    
    status_input_msg = pthread_join(input_msg_tid, &res_input);
    if(status_input_msg != SUCCESS)
    {
        handle_error_en(status_input_msg, "join input_ptrhead");
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
    
    if (res_input == PTHREAD_CANCELED)
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

void* listen_data(void *args_ptr)
{
    shed *args = args_ptr;
    char input_box[MQ_BUFF_SIZE];
    char curr_client_queue_buff[15];

    printf("|SERVER-DATA| - Listen data queue\n");

    while (1)
    {
        if(mq_receive(args->data_d, input_box, MQ_BUFF_SIZE, NULL) > 0)
        {
            printf("|SERVER-DATA| - New client connection...\n");
            args->pid[args->client_count] = atoi(input_box);
            sprintf(curr_client_queue_buff, "/client_%d", args->pid[args->client_count]);
            args->client_d[args->client_count] = mq_open(curr_client_queue_buff, O_WRONLY | O_CREAT, 0777,&queue_attr);
            if(args->client_d[args->client_count] == ERROR)
            {
                handle_error_en(args->client_d[args->client_count], "Connection ERROR\n");
            }
            else
            {
                printf("|SERVER-DATA| - Client[%d] connect\n",args->pid[args->client_count]);
                args->client_count++;
            }
        }
        /*else
        {
            printf("|SERVER-DATA| - Whait clients\n");
            sleep(2);
            continue;
        }*/
    }
    return SUCCESS;
}

void* listen_chat(void *args_ptr)
{
    shed *args = args_ptr;
    char input_box[MQ_BUFF_SIZE];

    printf("|SERVER-CHAT| - Listen char queue\n");

    while (1)
    {
        if(mq_receive(args->chat_d, input_box, strlen(input_box), NULL) > 0)
        {
            printf("|SERVER-CHAT| - new msg\n");
            for(int i = 0; i < args->client_count; i++)
            {
                while (mq_send(args->client_d[i], input_box, strlen(input_box), 0) != 0){}
            }
            printf("|SERVER-CHAT| -  Msg from Client[%s] add to queues\n", strtok(input_box, ":"));
            memset(input_box, 0, sizeof(input_box));
        }
        /*else
        {
            printf("|SERVER-CHAT| - Whait new msg from clients\n");
            sleep(1);
            continue;
        }*/
    }
    return SUCCESS;
}

void* listen_input_msg()
{
    char input_box[MQ_BUFF_SIZE];

    while (1)
    {
        fgets(input_box, MQ_BUFF_SIZE, stdin);

        if (strcmp(input_box, "/exit\n") == 0)
        {
            pthread_exit(NULL);
        }
    }

    return SUCCESS;
}
