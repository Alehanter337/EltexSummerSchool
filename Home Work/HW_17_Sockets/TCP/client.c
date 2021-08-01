#include "headers.h"

int main(int argc, char *argv[])
{
    struct sockaddr_un server;
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, SOCKET_PATH, sizeof(server.sun_path) - 1);

    int fd_data = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(fd_data == ERROR)
    {
        handle_error("socket()");
    }
    else
    {
        printf("|CLIENT| - socket create\n");
    }

    int rq = connect(fd_data, (const struct sockaddr *) &server,
                  sizeof(struct sockaddr_un));
    if(rq == ERROR)
    {
        handle_error("connect()");
    }
    else
    {
        printf("|CLIENT| - connect complete\n");
    }
    
    char buff[BUFF_SIZE];
    
    for (int i = 1; i < argc; i++)
    {
        rq = write(fd_data, argv[i], strlen(argv[i]) + 1);
        if(rq == ERROR)
        {
            handle_error("write()");
        }
        else
        {
            printf("|CLIENT| - write complete\n");
        }

        rq = read(fd_data, buff, BUFF_SIZE);
        if(rq == -1)
        {
            handle_error("read()");
        }
        else
        {
            printf("|CLIENT| - read complete\n");
        }

        printf("|CLIENT| - msg sent:[%s]\n", argv[i]);
        printf("|CLIENT| - echo msg received: %s\n\n", buff);
    }

    strcpy(buff, "/exit");
    rq = write(fd_data, buff, BUFF_SIZE);
    if (rq == -1) 
    {
        handle_error("last write()");
    }
    else {
        printf("|CLIENT| - last write complete\n");
    }
    close(fd_data);
    exit(EXIT_FAILURE);
}
