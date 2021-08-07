#include "headers.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main()
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	int port = 7331;
    server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	int fd_data = socket(AF_INET, SOCK_STREAM, 0);
	if (fd_data == ERROR) 
    {
	    handle_error("socket()");
    }
    else
    {
        printf("|CLIENT| - Socket created\n");
    }

	int ret = connect(fd_data, (const struct sockaddr *) &server,
	                  sizeof(struct sockaddr_in));
	if (ret == ERROR) 
    {
	    handle_error("connect()");
    }
    else
    {
        printf("|CLIENT| - Connect done\n");
    }
    
    while (1) 
    {
    	char buffer[MAX_MSG_SIZE] = {0};
		printf("|CLIENT| - Enter MSG\n");
		fgets(buffer, MAX_MSG_SIZE, stdin);

		ret = send(fd_data, buffer, strlen(buffer) - 1, 0);
		if (ret == ERROR)
        {
		    handle_error("send()");
        }
        else
        {
		    printf("|CLIENT| - Send[%s]\n", buffer);
        }

		if (strncmp(buffer, "/exit", 3) == 0)
        {
			break;
        }

		ret = recv(fd_data, buffer, MAX_MSG_SIZE, 0);
		if (ret == ERROR) 
        {
		    handle_error("recv()");
        }
        else
        {
            printf("|CLIENT| - Recv done\n");
        }

		printf("|CLIENT| - MSG received: %s\n\n", buffer);
	}

	close(fd_data);

    exit(EXIT_SUCCESS);
}
