#include "headers.h"

int main(void)
{
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    int port = 7331;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    
    int fd_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd_socket == ERROR)
    {
        handle_error("socket()");
    }
    else
    {
        printf("|SERVER| - Socket created\n");
    }

    int rq = bind(fd_socket, (const struct sockaddr *) &server,
                  sizeof(struct sockaddr_in));
    if(rq == -1)
    {
        handle_error("bind()");
    }
    else
    {
        printf("|SERVER| - Bind complete\n");
    }

    char buff[BUFF_SIZE];

     for (int i = 0; i < 2; i++)
     {
         rq = recvfrom(fd_socket, buff, BUFF_SIZE, 0, NULL, NULL);
         printf("|SERVER| - msg received: %s\n", buff);
     }

     close(fd_socket);
     exit(EXIT_SUCCESS);
}
