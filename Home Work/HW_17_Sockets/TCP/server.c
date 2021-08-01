#include "headers.h"

int main(void)
{
    struct sockaddr_un server;
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, SOCKET_PATH, sizeof(server.sun_path) - 1);
    
    int fd_socket = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(fd_socket == ERROR)
    {
        handle_error("socket()");
    }
    else 
    {
        printf("|SERVER| - socket create\n");
    }

    int rq = bind(fd_socket, (const struct sockaddr *) &server,
                  sizeof(struct sockaddr_un));
    if(rq == ERROR)
    {
        handle_error("bind()");
    }
    else
    {
        printf("|SERVER| - bind complete\n");
    }

    if (listen(fd_socket, 1) == ERROR)
    {
        handle_error("listen()");
    }
    else 
    {
        printf("|SERVER| - listening clients\n");
    }

    int fd_data = accept(fd_socket, NULL, NULL);
    if(fd_data == ERROR)
    {
        handle_error("accept()");
    }
    else 
    {
        printf("|SERVER| - Accept\n");
    }
    
    char buff[BUFF_SIZE];

    while (1) 
    {
        rq = recv(fd_data, buff, BUFF_SIZE, 0);
        if(rq == ERROR)
        {
            handle_error("recv()_1");
        }
        else 
        {
            printf("|SERVER| - recv complete\n");
        }

        if (strncmp(buff, "/exit", BUFF_SIZE) == 0) 
        {
            close(fd_data);
            break;
        }

        strcat(buff, " from server");
        rq = send(fd_data, buff, BUFF_SIZE, 0);
        if(rq == ERROR)
        {
            handle_error("recv()_2");
        }
        else {
            printf("|SERVER| - echo recv complete\n");
        }
    }

    close(fd_socket);
    unlink(SOCKET_PATH);
    exit(EXIT_SUCCESS);
}
